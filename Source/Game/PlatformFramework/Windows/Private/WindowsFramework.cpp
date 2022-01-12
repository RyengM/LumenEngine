#include "Game/PlatformFramework/Windows/Public/WindowsFramework.h"
#include "Render/RenderCore/Public/RenderCommand.h"
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

    // We regard preinit as the first frame, we can enqueue render command at preinit stage
    RenderCommandQueue::GetInstance().BeginEnqueue();
    // Make sure backend device is prepared before init
    pFramework->InitDevice();
    pFramework->InitUI();
    pFramework->PreInit();
    RenderCommandQueue::GetInstance().EndEnqueue();

    // We regard init as the second frame, we can enqueue render command at init stage
    RenderCommandQueue::GetInstance().BeginEnqueue();
    // Make sure win imgui is prepared when imgui dx backend is initialized
    pFramework->Init();
    RenderCommandQueue::GetInstance().EndEnqueue();
    
    // Wait until the first frame is done, it means dx12 device is established
    while (!RenderCommandQueue::GetInstance().IsEmpty());

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
            // If command queue is full, do nothing, else start this frame
            if (!RenderCommandQueue::GetInstance().BeginEnqueue()) continue;
            pFramework->UpdateUI();
            pFramework->Tick();
            RenderCommandQueue::GetInstance().EndEnqueue();
        }
    }

    // Wait for render thread finish all work
    while (!RenderCommandQueue::GetInstance().IsEmpty());

    // Exit
    pFramework->Exit();
    pFramework->Clean();

    // Delete the framework
    delete pFramework;

    // return this part of the WM_QUIT message
    return static_cast<char>(msg.wParam);
}

void WindowsFramework::InitDevice()
{
    ENQUEUE_RENDER_COMMAND("InitDevice", [this](FrameRenderContext* renderContext, GraphicsRHI* graphicsRHI) {
        graphicsRHI->SetClientResolution(mClientWidth, mClientHeight);
        if (!graphicsRHI->InitDirect3D(this->mhMainWnd))
        {
            LOG_ERROR("Device create failed, program exists");
            exit(0);
        }
        LOG_INFO("Graphics device iniatialized");
    });
}

void WindowsFramework::InitUI()
{
    mImguiManager.Init(mhMainWnd, mEngine.GetConfig().frameBufferNum);
    gImguiManager = &mImguiManager;
    
    ENQUEUE_RENDER_COMMAND("InitUI", [this](FrameRenderContext* renderContext, GraphicsRHI* graphicsRHI) {
        graphicsRHI->InitUI();
        graphicsRHI->OnResize();
        graphicsRHI->CreateUIDeviceObject();
        LOG_INFO("UI iniatialized");
    });
}

void WindowsFramework::UpdateUI()
{
    ImGui_ImplWin32_NewFrame_Shared();

    for (auto context : mImguiManager.GetContexts())
    {
        ImGui::SetCurrentContext(context);
        ImGui_ImplWin32_NewFrame_Context(context, { 0.f, 0.f }, (float)mClientWidth, (float)mClientHeight);
        ImGui::NewFrame();

        UpdateGuiWindow();
        // Prepare data to current context.DrawData
        ImGui::Render();
        // Create proxy and submit to render context
        DrawDataProxy* proxy = mImguiManager.CreateContextDrawDataProxy(context, mEngine.GetCurrFrame());
        mEngine.SubmitGUIPorxy(proxy->mDrawData);
    }
    // Update UI in render thread
    ENQUEUE_RENDER_COMMAND("UpdateUI", [](FrameRenderContext* renderContext, GraphicsRHI* graphicsRHI) {
        for (auto drawData : renderContext->guiProxies)
            graphicsRHI->DrawUI(static_cast<ImDrawData*>(drawData));
    });
}

void WindowsFramework::Clean()
{
    mImguiManager.Clear();
}

bool bShowDemoWindow = true;
bool bShowAnotherWindow = false;
ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void WindowsFramework::UpdateGuiWindow()
{
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (bShowDemoWindow)
        ImGui::ShowDemoWindow(&bShowDemoWindow);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &bShowDemoWindow);       // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &bShowAnotherWindow);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clearColor);  // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (bShowAnotherWindow)
    {
        ImGui::Begin("Another Window", &bShowAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            bShowAnotherWindow = false;
        ImGui::End();
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
    RECT R = { 0, 0, mClientWidth, mClientHeight };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;

    mhMainWnd = CreateWindow(mWndClass.lpszClassName, mName,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mWndClass.hInstance, 0);
    if (!mhMainWnd)
    {
        MessageBox(0, L"CreateWindow Failed.", 0, 0);
        return false;
    }

    ShowWindow(mhMainWnd, SW_SHOW);
    UpdateWindow(mhMainWnd);

    return true;
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler_Context(ImGuiContext* ctx, bool ingore_mouse, bool ingore_keyboard, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Message handler
LRESULT CALLBACK WindowsFramework::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (gImguiManager)
        for (auto context : gImguiManager->GetContexts())
            if (ImGui_ImplWin32_WndProcHandler_Context(context, false, false, hWnd, message, wParam, lParam))
                return true;

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