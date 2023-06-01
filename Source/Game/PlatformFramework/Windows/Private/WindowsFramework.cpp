#include "Game/PlatformFramework/Windows/Public/WindowsFramework.h"
#include "Game/PlatformFramework/Windows/Public/imgui_impl_win32.h"
#include "Game/Asset/Public/Serializer.h"
#include "Game/GamePlay/Public/MeshEntity.h"
#include "ThirdParty/Imgui/imgui_stdlib.h"
#include "ThirdParty/Imgui/imgui_internal.h"
#include "Render/RenderCore/Public/RenderCommand.h"
#include "Render/RHI/D3D12/Public/D3DContext.h"
#include <cassert>
#include <WindowsX.h>
#include <filesystem>

using namespace Lumen::Game;
using namespace Lumen::Core;
using namespace Lumen::Render;
using namespace std::filesystem;

static WindowsFramework* gWindowsFramework = nullptr;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return gWindowsFramework->WindowProc(hwnd, msg, wParam, lParam);
}

// Static method for engine launch, program main body
int WindowsFramework::RunFramework(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, WindowsFramework* pFramework)
{
    gWindowsFramework = pFramework;

    if (!pFramework->InitMainWindow())
        return 0;
 
    // We need to assign gImGui first, which will be used in render thread for gpu resource initialization
    pFramework->InitUI();

    pFramework->PreInit(pFramework->mWindowInfo);

    RenderCommandQueue::GetInstance().BeginEnqueue();
    pFramework->Init();
    RenderCommandQueue::GetInstance().EndEnqueue();

    // Main loop
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        // Check to see if any messages are waiting in the queue
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);                             // Translate keystroke messages into the right format            
            DispatchMessage(&msg);                              // Send the message to the WindowProc function
            if (!pFramework->HandleIO()) break;
        }
        else
        {
            // If command queue is full, do nothing, else start this frame
            if (!RenderCommandQueue::GetInstance().BeginEnqueue()) continue;
            pFramework->Tick();
            pFramework->UpdateUI();
            RenderCommandQueue::GetInstance().EndEnqueue();
        }
    }

    // Wait for render thread and GPU finish all work, do later
    // Now just sleep for a while
    Sleep(100);

    // Exit
    pFramework->Exit();
    pFramework->Clean();

    // Delete the framework
    gWindowsFramework = nullptr;
    delete pFramework;

    // return this part of the WM_QUIT message
    return static_cast<char>(msg.wParam);
}

void WindowsFramework::InitUI()
{
    mImguiManager.Init(mEngine.GetConfig().frameBufferNum);
    mWindowFlags |= ImGuiWindowFlags_MenuBar;

    mFileBrowser = ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal);

    ImGui_ImplWin32_Init(mWindowInfo.mainWnd);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("../../Assets/Font/msyh.ttc", 17.f, NULL);
    io.Fonts->Build();
}

void WindowsFramework::UpdateUI()
{
    for (auto context : mImguiManager.GetContexts())
    {
        ImGui::SetCurrentContext(context);
        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
        UpdateGuiWindow();
        // Prepare data to current context.DrawData
        ImGui::Render();
        // Create proxy and submit to render context
        DrawDataProxy* proxy = mImguiManager.CreateContextDrawDataProxy(context);

        if (proxy->mDrawData->CmdListsCount == 0) continue;

        // Update UI in render thread
        ENQUEUE_RENDER_COMMAND("UpdateUI", [proxy](RHIContext* graphicsContext) {
            graphicsContext->DrawUI(proxy->mDrawData);
        });
    }
}

void WindowsFramework::Clean()
{
    mImguiManager.Clear();
}

static AssetTreeNode* activeAssetNode = nullptr;
// Selected entity in hierarchy
static int selected = 0;
// If entity asset bind is changed manually
static bool bAssetBindChanged = false;
// If asset is binding: guid is bind but name is not changed
static bool bAssetBinding = false;
// Asset bind name
std::string assetBindName = "";
// If is in text input mode
static bool bTextInput = false;
// 0: entity, 1: material asset file
static int detailShowType = 0;
// Current material shown in detail
Material* matShownInDetail;
// Current asset target position type, used to specific the type of drag asset
std::string currentAssetTargetType = "";

void WindowsFramework::UpdateGuiWindow()
{
    // Move camera
    Scene* scene = AssetManager::GetInstance().GetScene();
    Camera* camera = dynamic_cast<Camera*>(scene->entities[0].get());
    if (ImGui::IsKeyDown(ImGuiKey_W) || ImGui::IsKeyDown(ImGuiKey_S) || ImGui::IsKeyDown(ImGuiKey_A) || ImGui::IsKeyDown(ImGuiKey_D))
        camera->ProcessKeyboard();

    // Save scene
    if (ImGui::IsKeyReleased(ImGuiKey_S) && mEngine.deviceStatus->leftCtrlActive)
        AssetManager::GetInstance().SaveScene();

    // Show simple profiler
    {
        ImGui::Begin("Profiler");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("GameThread Tick %.2f (ms)", mEngine.GetProfileData()->gameThreadTickTime / 1000.f);
        ImGui::Text("RenderThread Tick %.2f (ms)", mEngine.GetProfileData()->renderThreadTickTime / 1000.f);
        ImGui::End();
    }

    // Show scene hierarchy
    {
        ImGui::Begin("Hierarchy", NULL, mWindowFlags);

        if (scene)
        {
            std::string wantToFind;
            ImGui::InputText(" ", &wantToFind, ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::SameLine();
            ImGui::Button("search");
            {
                for (int i = 0; i < scene->entities.size(); i++)
                    if (scene->entities[i].get() && wantToFind == scene->entities[i]->GetName().c_str())
                        selected = i;
            }

            //MenuBar
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Menu"))
                {
                    UpdateGuiWindowHierarchyMenuBar(scene);
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            // Show or rename entity
            for (int i = 0; i < scene->entities.size(); i++)
            {
                auto& entity = scene->entities[i];
                if (!entity.get()) continue;
                // Normal frame
                if (!bTextInput || selected != i)
                {
                    if (ImGui::Selectable(entity->GetName().c_str(), selected == i))
                    {
                        detailShowType = 0;
                        selected = i;
                    }
                }
                // Rename frame
                else
                {
                    std::string name = entity->GetName();
                    if (selected == i && ImGui::InputText("new name##rename", &name, ImGuiInputTextFlags_EnterReturnsTrue))
                    {
                        if (name == "") { bTextInput = false; continue; }      // empty name
                        entity->SetName(name);
                        bTextInput = false;
                    }
                }
                // Trigger rename
                if (ImGui::IsMouseDoubleClicked(0) && selected == i && ImGui::IsItemActivated())
                    bTextInput = true;
            }
            // Delete entity by delete key
            if (ImGui::IsWindowHovered() && ImGui::IsKeyReleased(ImGuiKey_Delete))
            {
                // Camera and Light can not be deleted now
                if (scene->entities.size() && selected != 0 && selected != 1)
                {
                    scene->entities[selected]->Destroy();
                    selected = 0;
                }
            }
            // Popup window to operate entities
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::TreeNode("Add entity"))
                {
                    for (auto t : rttr::type::get_types())
                    {
                        if (t.is_derived_from<Entity>() && t.is_class())
                        {
                            auto name = t.get_name();
                            // Do not support create camera and light yet
                            if (name == "Camera" || name == "DirectionalLight")
                                continue;
                            if (ImGui::Button(name.data()))
                                scene->CreateEntity(name.data());
                        }
                    }
                    ImGui::TreePop();
                }
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

    // Show object detail
    {
        ImGui::Begin("Detail");
        // Show entity detail
        if (detailShowType == 0)
        {
            if (scene && scene->entities.size())
            {
                Entity* selectedEntity = scene->entities[selected].get();
                ShowDetailInternal(selectedEntity);
            }
            // Save scene
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Button("Save"))
                {
                    AssetManager::GetInstance().SaveScene();
                }
                ImGui::EndPopup();
            }
        }
        // Show asset file detail
        else if (detailShowType == 1)
        {
            ShowDetailInternal(matShownInDetail);

            // Save material
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Button("Save"))
                {
                    Serializer::GetInstance().Serialize(matShownInDetail, matShownInDetail->path);
                }
                ImGui::EndPopup();
            }
        }
        ImGui::End();

        // Update entity data bind in render thread if data bind is changed
        if (bAssetBindChanged)
        {
            // Update info in render side
            if (scene && scene->entities.size())
            {
                Entity* selectedEntity = scene->entities[selected].get();
                scene->UpdateEntity(selectedEntity);
            }
            bAssetBindChanged = false;
        }
    }

    // Show asset manager
    {
        ImGui::Begin("Asset maneger");
        ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;
        if (ImGui::BeginTable("Assets", 2, flags))
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            if (ImGui::TreeNode("Assets"))
                EnterDictRecur(AssetManager::GetInstance().GetAssetTree());

            ImGui::TableSetColumnIndex(1);
            // Show files in folder context
            ShowFolderContext();
            ImGui::EndTable();
        }
        // Popup window to create new assets
        if (ImGui::BeginPopupContextWindow())
        {
            // Material
            if (ImGui::Button("Create material"))
            {
                mFileBrowser.Open();
            }
            ImGui::EndPopup();
        }
        ImGui::End();

        mFileBrowser.Display();

        std::filesystem::path selectedFilePath;
        if (mFileBrowser.HasSelected())
        {
            selectedFilePath = mFileBrowser.GetSelected().string();
            if (selectedFilePath.extension() == ".shader")
            {
                mFileBrowser.ClearSelected();
                std::filesystem::path metaPath = std::filesystem::path(selectedFilePath).concat(".meta");
                if (std::filesystem::exists(metaPath))
                {
                    Meta meta;
                    Serializer::GetInstance().Deserialize(&meta, metaPath.string());
                    AssetManager::GetInstance().CreateMaterial(xg::Guid(meta.guid));
                }
            }
        }
    }

    // Show render tagret
    {
        ImGui::Begin("Scene", NULL, ImGuiWindowFlags_MenuBar);

        if (ImGui::IsWindowHovered())
            mEngine.deviceStatus->bSceneWindow = true;
        else
            mEngine.deviceStatus->bSceneWindow = false;

        auto CreateEntity = [scene](const std::string& builtinMesh)
        {
            if (builtinMesh != "")
            {
                MeshEntity* entity = dynamic_cast<MeshEntity*>(scene->CreateEntity("MeshEntity"));
                if (entity)
                {
                    entity->SetMeshGUID(builtinMesh + "-builtin");
                    scene->UpdateEntity(entity);
                }
            }
        };

        static bool bCreateCube = false;
        static bool bCreateSphere = false;
        static bool bCreatePlane = false;
        static bool bBeginPlay = false;
        static bool bEndPlay = false;

        if (bCreateCube)    CreateEntity("cube");
        if (bCreateSphere)  CreateEntity("sphere");
        if (bCreatePlane)   CreateEntity("plane");

        bCreateCube = false;
        bCreateSphere = false;
        bCreatePlane = false;
        bBeginPlay = false;
        bEndPlay = false;

        // Show control panel
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Objects"))
            {
                ImGui::MenuItem("Cube", NULL, &bCreateCube);
                ImGui::MenuItem("Sphere", NULL, &bCreateSphere);
                ImGui::MenuItem("Plane", NULL, &bCreatePlane);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Actions"))
            {
                ImGui::MenuItem("Start", NULL, &bBeginPlay);
                ImGui::MenuItem("Stop", NULL, &bEndPlay);
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        // Show scene RT
        if (mEngine.GetSceneBufferPtr()->srvHandle && mEngine.GetSceneBufferPtr()->srvHandle != 0xcdcdcdcdcdcdcdcd)
        {
            ImGuiWindow* guiWindow = ImGui::FindWindowByName("Scene");
            auto sceneBufPtr = mEngine.GetSceneBufferPtr();
            //ImGui::Image((ImTextureID)sceneBufPtr->srvHandle, ImVec2(sceneBufPtr->width, sceneBufPtr->height));
            ImVec2 Rect(guiWindow->InnerRect.GetSize().x, guiWindow->InnerRect.GetSize().y - guiWindow->TitleBarRect().GetSize().y);
            ImGui::Image((ImTextureID)sceneBufPtr->srvHandle, Rect);
        }
        ImGui::End();
    }
}

void WindowsFramework::EnterDictRecur(AssetTreeNode* node)
{
    for (auto childNode : node->children)
    {
        if (childNode->fileType == "Directory")
        {
            if (ImGui::TreeNode(childNode->fileName.data()))
                EnterDictRecur(childNode.get());
        }
        if (ImGui::IsItemClicked())
            activeAssetNode = childNode.get();
    }
    ImGui::TreePop();
}

void WindowsFramework::ShowFolderContext()
{
    if (!activeAssetNode) return;

    ImGuiStyle& style = ImGui::GetStyle();
    float windowVisible = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    for (auto node : activeAssetNode->children)
    {
        // If asset button is pressed, show file detail
        if (ImGui::Button(node->fileName.c_str()))
        {
            std::filesystem::path path = node->fileName;
            // Matrial
            if (path.extension() == ".mat")
            {
                matShownInDetail = AssetManager::GetInstance().GetMaterialByGUID(xg::Guid(node->fileGuid));
                detailShowType = 1;
            }
        }
        float nextButton = ImGui::GetItemRectMax().x + style.ItemSpacing.x + ImGui::CalcTextSize(node->fileName.c_str(), NULL, true).x;
        if (nextButton < windowVisible)
            ImGui::SameLine();

        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("FileBind", node.get(), sizeof(AssetTreeNode), ImGuiCond_Once);
            ImGui::Text(node->fileName.c_str());
            ImGui::EndDragDropSource();
        }
    }
}

void WindowsFramework::ShowDetailInternal(rttr::instance obj)
{
    type t = obj.get_derived_type();
    if (t.is_wrapper())
    {
        instance wrappedInstance = obj.get_wrapped_instance();
        t = wrappedInstance.get_derived_type();
    }
    for (auto& p : t.get_properties(filter_item::instance_item | filter_item::non_public_access | filter_item::public_access))
    {
        if (p.get_metadata("serialize").is_valid() && p.get_metadata("serialize").to_bool())
        {
            variant var = p.get_value(obj);
            BindVariant(p, var);
            // Must read back to modify origin data
            p.set_value(obj, var);
        }
    }
}

void WindowsFramework::BindVariant(const rttr::property& p, rttr::variant& var)
{
    auto t = var.get_type();
    // Arithmetic
    if (ShowDetailAtomic(p, var)) {}
    // Array type
    //else if (var.is_sequential_container())
    //    ShowDetailSequential(p, var.create_sequential_view());
    // Key-value type
    else if (var.is_associative_container())
        ShowDetailAssociative(p, var.create_associative_view());
    // Object
    else
    {
        // Special handling for Vec3 type, because item with same label name will be recognized as same one in imgui
        if (t.get_name() == "Vec3")
        {
            ImGui::DragFloat3(p.get_name().data(), &var.get_value<Vec3>().x, 0.1f);
            return;
        }
        if (ImGui::CollapsingHeader(p.get_name().data()))
        {
            auto childProps = t.get_properties();
            if (!childProps.empty())
                ShowDetailInternal(var);

            if (ImGui::IsItemHovered())
            {
                currentAssetTargetType = p.get_name().to_string();
            }
        }
    }
}

bool WindowsFramework::ShowDetailAtomic(const rttr::property& p, rttr::variant& var)
{
    auto propertyName = p.get_name().data();
    auto t = var.get_type();
    if (t.is_arithmetic())
    {
        if (t == type::get<bool>())
            ImGui::Checkbox(propertyName, &var.get_value<bool>());
        else if (t == type::get<int8_t>() || t == type::get<int16_t>() || t == type::get<int32_t>() || t == type::get<int64_t>() ||
            t == type::get<uint8_t>() || t == type::get<uint16_t>() || t == type::get<uint32_t>() || t == type::get<uint64_t>())
            ImGui::DragInt(propertyName, &var.get_value<int>(), 1);
        else if (t == type::get<float>() || t == type::get<double>())
            ImGui::DragFloat(propertyName, &var.get_value<float>(), 0.1f);
        return true;
    }
    else if (t == type::get<std::string>())
    {
        ImGui::LabelText(propertyName, var.to_string().c_str());

        // Drag data bind and update info in editor
        if (p.get_name() == "name" && p.get_declaring_type().get_name() == "AssetRef" && bAssetBinding)
        {
            var.get_value<std::string>() = assetBindName;
            bAssetBinding = false;
        }
        if (p.get_name() == "guid" && p.get_declaring_type().get_name() == "AssetRef")
        {
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FileBind"))
                {
                    AssetTreeNode* node = (AssetTreeNode*)payload->Data;
                    std::string guid = node->fileGuid;
                    std::filesystem::path path = node->fileName;
                    // Asset bind
                    if (path.extension() == ".obj" && currentAssetTargetType == "mMeshContainer" ||                                // Mesh bind
                        (path.extension() == ".png" || path.extension() == ".jpg") && currentAssetTargetType == "propertyList" ||  // Texture bind
                        path.extension() == ".mat" && currentAssetTargetType == "mMeshRenderer")                                   // Material bind
                    {
                        var.get_value<std::string>() = guid;
                        assetBindName = path.stem().string();
                        bAssetBinding = true;
                        bAssetBindChanged = true;
                    }
                }
                ImGui::EndDragDropTarget();
            }
        }
        return true;
    }
    return false;
}

bool WindowsFramework::ShowDetailSequential(const rttr::property& p, const rttr::variant_sequential_view& view)
{
    for (auto& item : view)
    {
        rttr::variant wrappedVar = item.extract_wrapped_value();
        rttr::type t = wrappedVar.get_type();
        if (t.is_arithmetic() || t == type::get<std::string>() || t.is_enumeration())
            ShowDetailAtomic(p, wrappedVar);
        else
            ShowDetailInternal(wrappedVar);
    }
    return true;
}

bool WindowsFramework::ShowDetailAssociative(const rttr::property& p, const rttr::variant_associative_view& view)
{
    if (view.is_key_only_type())
        for (auto& item : view)
            BindVariant(p, const_cast<variant&>(item.first));
    else
    {
        for (auto& item : view)
        {
            rttr::type t = item.second.get_type().get_wrapped_type();
            if (t.is_arithmetic())
            {
                if (t == type::get<bool>())
                    ImGui::Checkbox(item.first.to_string().c_str(), &const_cast<bool&>(item.second.get_wrapped_value<bool>()));
                else if (t == type::get<int8_t>() || t == type::get<int16_t>() || t == type::get<int32_t>() || t == type::get<int64_t>() ||
                    t == type::get<uint8_t>() || t == type::get<uint16_t>() || t == type::get<uint32_t>() || t == type::get<uint64_t>())
                    ImGui::DragInt(item.first.to_string().c_str(), &const_cast<int&>(item.second.get_wrapped_value<int>()), 1);
                else if (t == type::get<float>() || t == type::get<double>())
                    ImGui::DragFloat(item.first.to_string().c_str(), &const_cast<float&>(item.second.get_wrapped_value<float>()), 0.1f);
            }
            else if (t == type::get<std::string>())
            {
                ImGui::LabelText(item.first.to_string().c_str(), item.second.to_string().c_str());
            }
            else if (t.get_name() == "Vec4") // Color
            {
                ImGui::ColorEdit4(item.first.to_string().c_str(), &const_cast<float&>(item.second.get_wrapped_value<Vec4>().x));
            }
            else // Object
            {
                ShowDetailInternal(item.second);
            }
        }
    }
    return true;
}

bool WindowsFramework::HandleIO()
{
    ImGuiContext& g = *GImGui;
    Camera* camera = dynamic_cast<Camera*>(AssetManager::GetInstance().GetScene()->entities[0].get());

    auto status = mEngine.deviceStatus.get();

    // Deal with responsive interaction
    for (auto& inputEvent : g.InputEventsQueue)
    {
        if (inputEvent.Type == ImGuiInputEventType::ImGuiInputEventType_MousePos)
        {
            float x = inputEvent.MousePos.PosX;
            float y = inputEvent.MousePos.PosY;

            status->ProcessMouseMovement(x, y);
            camera->ProcessMouseMovement();
        }
        else if (inputEvent.Type == ImGuiInputEventType::ImGuiInputEventType_MouseButton)
        {
            if (inputEvent.MouseButton.Button == 1)
            {
                if (inputEvent.MouseButton.Down)
                    status->rightMouseActive = true;
                else status->rightMouseActive = false;
            }
        }
        else if (inputEvent.Type == ImGuiInputEventType::ImGuiInputEventType_Key)
        {
            if (inputEvent.Key.Key == ImGuiKey_Escape)
                return false;
            if (inputEvent.Key.Key == ImGuiKey_W)
            {
                if (inputEvent.Key.Down) status->wPressed = true;
                else status->wPressed = false;
            }
            if (inputEvent.Key.Key == ImGuiKey_S)
            {
                if (inputEvent.Key.Down) status->sPressed = true;
                else status->sPressed = false;

            }
            if (inputEvent.Key.Key == ImGuiKey_A)
            {
                if (inputEvent.Key.Down) status->aPressed = true;
                else status->aPressed = false;
            }
            if (inputEvent.Key.Key == ImGuiKey_D)
            {
                if (inputEvent.Key.Down) status->dPressed = true;
                else status->dPressed = false;
            }
            if (inputEvent.Key.Key == ImGuiKey_LeftCtrl)
            {
                if (inputEvent.Key.Down) status->leftCtrlActive = true;
                else status->leftCtrlActive = false;
            }
        }
    }
    return true;
}

void WindowsFramework::UpdateGuiWindowHierarchyMenuBar(Scene* scene)
{
    if (ImGui::BeginMenu("New"))
    {
        for (auto t : rttr::type::get_types())
        {
            if (t.is_derived_from<Entity>() && t.is_class())
            {
                auto name = t.get_name();
                // Do not support create camera and light yet
                if (name == "Camera" || name == "DirectionalLight")
                    continue;
                if (ImGui::Button(name.data()))
                    scene->CreateEntity(name.data());
            }
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Delete"))
    {
        if (scene->entities.size() && selected != 0 && selected != 1)
        {
            scene->entities[selected]->Destroy();
            selected = 0;
        }
    }
    if (ImGui::MenuItem("Rename"))
        bTextInput = true;
}

bool WindowsFramework::InitMainWindow()
{
    mWndClass.style = CS_HREDRAW | CS_VREDRAW;
    mWndClass.lpfnWndProc = MainWndProc;
    mWndClass.cbClsExtra = 0;
    mWndClass.cbWndExtra = 0;
    mWndClass.hInstance = mhAppInst;
    mWndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
    mWndClass.hCursor = LoadCursor(0, IDC_ARROW);
    mWndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    mWndClass.lpszMenuName = 0;
    mWndClass.lpszClassName = L"MainWindow";

    if (!RegisterClass(&mWndClass))
    {
        MessageBox(0, L"RegisterClass Failed.", 0, 0);
        return false;
    }

    // Compute window rectangle dimensions based on requested client area dimensions.
    RECT R = { 0, 0, mWindowInfo.clientWidth, mWindowInfo.clientHeight };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;

    mWindowInfo.mainWnd = CreateWindow(mWndClass.lpszClassName, mName,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mWndClass.hInstance, 0);
    if (!mWindowInfo.mainWnd)
    {
        MessageBox(0, L"CreateWindow Failed.", 0, 0);
        return false;
    }

    ShowWindow((HWND)mWindowInfo.mainWnd, SW_SHOW);
    UpdateWindow((HWND)mWindowInfo.mainWnd);

    return true;
}

void WindowsFramework::OnResize()
{
    mEngine.OnResize(mWindowInfo);
}

// Forward declare message handler from imgui_impl_win32.h
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Message handler
LRESULT CALLBACK WindowsFramework::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    for (auto context : mImguiManager.GetContexts())
    {
        ImGui::SetCurrentContext(context);
        if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
            return true;
    }

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_SIZE:
    {
        if (wParam != SIZE_MINIMIZED)
        {
            mWindowInfo.clientWidth = LOWORD(lParam);
            mWindowInfo.clientHeight = HIWORD(lParam);
            OnResize();
        }

        return 0;
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}