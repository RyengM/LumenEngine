#include "Game/PlatformFramework/Windows/Public/WindowsFramework.h"
#include "Core/Logger/Public/Logger.h"
#include <cassert>
#include <WindowsX.h>

using namespace Lumen::Game;
using namespace Lumen::Core;

// Static method for engine launch
int WindowsFramework::RunFramework(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, WindowsFramework* pFramework)
{
    if (!pFramework->InitMainWindow())
        return 0;

    // Init Engine
    pFramework->PreInit();
    pFramework->Init();

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
            pFramework->Tick();
    }

    // Exit
    pFramework->Exit();

    // Delete the framework
    delete pFramework;

    // return this part of the WM_QUIT message
    return static_cast<char>(msg.wParam);
}

bool WindowsFramework::InitMainWindow()
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = mhAppInst;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = "MainWindow";

    if (!RegisterClass(&wc))
    {
        MessageBox(0, "RegisterClass Failed.", 0, 0);
        return false;
    }

    // Compute window rectangle dimensions based on requested client area dimensions.
    RECT R = { 0, 0, mClientWidth, mClientHeight };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;

    mhMainWnd = CreateWindow("MainWindow", GetName(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, 0);
    if (!mhMainWnd)
    {
        MessageBox(0, "CreateWindow Failed.", 0, 0);
        return false;
    }

    ShowWindow(mhMainWnd, SW_SHOW);
    UpdateWindow(mhMainWnd);

    return true;
}

// Message handler
LRESULT CALLBACK WindowsFramework::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
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