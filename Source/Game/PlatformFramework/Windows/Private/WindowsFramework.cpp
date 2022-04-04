#include "Game/PlatformFramework/Windows/Public/WindowsFramework.h"
#include "Game/PlatformFramework/Windows/Public/imgui_impl_win32.h"
#include "Render/RenderCore/Public/RenderCommand.h"
#include "Render/RHI/D3D12/Public/D3DContext.h"
#include <cassert>
#include <WindowsX.h>

using namespace Lumen::Game;
using namespace Lumen::Core;
using namespace Lumen::Render;

// Static method for engine launch, program main body
int WindowsFramework::RunFramework(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, WindowsFramework* pFramework)
{
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
        }
        else
        {
            pFramework->HandleIO();
            // If command queue is full, do nothing, else start this frame
            if (!RenderCommandQueue::GetInstance().BeginEnqueue()) continue;
            pFramework->Tick();
            pFramework->UpdateUI();
            RenderCommandQueue::GetInstance().EndEnqueue();
        }
    }

    // Wait for render thread finish all work, need to consider GPU side, do later
    /*while (!RenderCommandQueue::GetInstance().IsEmpty());*/

    // Exit
    pFramework->Exit();
    pFramework->Clean();

    // Delete the framework
    delete pFramework;

    // return this part of the WM_QUIT message
    return static_cast<char>(msg.wParam);
}

void WindowsFramework::InitUI()
{
    mImguiManager.Init(mEngine.GetConfig().frameBufferNum);
    gImguiManager = &mImguiManager;

    ImGui_ImplWin32_Init(mWindowInfo.mainWnd);
    // Make sure fonts is initialized
    unsigned char* pixels;
    int width, height;
    ImGui::GetIO().Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
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

void WindowsFramework::UpdateGuiWindow()
{
    static int selected = 0;

    // Show simple profiler
    {
        ImGui::Begin("Profiler");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("GameThread Tick %.2f (ms)", mEngine.GetProfileData()->gameThreadTickTime / 1000.f);
        ImGui::Text("RenderThread Tick %.2f (ms)", mEngine.GetProfileData()->renderThreadTickTime / 1000.f);
        ImGui::End();
    }
    
    // Show render tagret
    {
        ImGui::Begin("Scene");
        if (mEngine.GetSceneBufferPtr()->srvHandle != 0xcdcdcdcdcdcdcdcd)
        {
            auto sceneBufPtr = mEngine.GetSceneBufferPtr();
            ImGui::Image((ImTextureID)sceneBufPtr->srvHandle, ImVec2(sceneBufPtr->width, sceneBufPtr->height));
        }
        ImGui::End();
    }

    // Show scene hierarchy
    {
        
        ImGui::Begin("Hierarchy");
        if (mEngine.GetScene())
        {
            for (int i = 0; i < mEngine.GetScene()->entities.size(); i++)
            {
                auto& entity = mEngine.GetScene()->entities[i];
                if (ImGui::Selectable(entity.GetName().c_str(), selected == i))
                    selected = i;
            }
        }
        ImGui::End();
    }

    // Show object detail
    {
        ImGui::Begin("Detail");
        ImGui::Text(mEngine.GetScene()->entities[selected].GetName().c_str());
        Entity* selectedEntity = &mEngine.GetScene()->entities[selected];
        if (ImGui::CollapsingHeader("Transform"))
        {
            auto transform = selectedEntity->GetTransform();
            ImGui::LabelText("label", "Value");
            {
                ImGui::DragFloat3("translate", reinterpret_cast<float*>(&transform->position));
                ImGui::DragFloat3("rotation", reinterpret_cast<float*>(&transform->rotation));
                ImGui::DragFloat3("scale", reinterpret_cast<float*>(&transform->scale));
            }
        }
        ImGui::End();
    }

    // Show asset manager
    {
        ImGui::Begin("Asset maneger");
        ImGui::End();
    }
}

// TODO
void WindowsFramework::HandleIO()
{
    ImGuiContext& g = *GImGui;

    for (auto& inputEvent : g.InputEventsQueue)
    {
        if (inputEvent.Type == ImGuiInputEventType::ImGuiInputEventType_MousePos)
        {

        }
    }
}

bool WindowsFramework::InitMainWindow()
{
    mWndClass.style = CS_HREDRAW | CS_VREDRAW;
    mWndClass.lpfnWndProc = WindowProc;
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

// Forward declare message handler from imgui_impl_win32.h
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Message handler
LRESULT CALLBACK WindowsFramework::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (gImguiManager)
        for (auto context : gImguiManager->GetContexts())
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