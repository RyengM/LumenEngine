#include "Game/PlatformFramework/Windows/Public/WindowsFramework.h"
#include "Core/Logger/Public/Logger.h"
#include <cassert>

using namespace Lumen::Game;
using namespace Lumen::Core;

static WindowsFramework* pFrameworkInstance = nullptr;

static bool bIsMinimized = false;
static RECT sWindowRect;
static LONG sBorderedStyle = 0;
static LONG sBorderlessStyle = 0;
static UINT sWindowStyle = 0;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Static method for engine launch
int RunFramework(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, WindowsFramework* pFramework)
{
    // Init window class
    HWND hWnd;
    WNDCLASSEX windowClass;

    ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = pFramework->GetName();
    windowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101)); // '#define ICON_IDI 101' is assumed to be included with resource.h
    if (windowClass.hIcon == NULL)
    {
        DWORD dw = GetLastError();
        if (dw == ERROR_RESOURCE_TYPE_NOT_FOUND)
            LOG_WARN("Warning: Icon file or .rc file not found, using default Windows app icon.");
        else
            LOG_WARN("Warning: error loading icon, using default Windows app icon.");
    }
    RegisterClassEx(&windowClass);

    // If this is null, nothing to do, bail
    assert(pFramework);
    if (!pFramework) return -1;
    pFrameworkInstance = pFramework;

    // Get command line and config file parameters for app run
    UINT32 Width = 1920;
    UINT32 Height = 1080;

    // Window setup based on config params
    sWindowStyle = WS_OVERLAPPEDWINDOW;
    RECT windowRect = { 0, 0, (LONG)Width, (LONG)Height };
    AdjustWindowRect(&windowRect, sWindowStyle, FALSE);         // Adjust the size

    // This makes sure that in a multi-monitor setup with different resolutions, get monitor info returns correct dimensions
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    // Create the window
    hWnd = CreateWindowEx(NULL,
        pFramework->GetName(),                                  // Name of the window class
        pFramework->GetName(),
        sWindowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        NULL,                                                   // We have no parent window, NULL
        NULL,                                                   // We aren't using menus, NULL
        hInstance,                                              // Application handle
        NULL);                                                  // Used with multiple windows, NULL

    // Init Engine
    pFramework->PreInit();
    pFramework->Init();

    // show the window
    ShowWindow(hWnd, nCmdShow);
    sBorderedStyle = GetWindowLong(hWnd, GWL_STYLE);
    sBorderlessStyle = sBorderedStyle & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);

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
        else if (!bIsMinimized)
            pFramework->Tick();
    }

    // Exit
    pFramework->Exit();

    // Delete the framework
    pFrameworkInstance = nullptr;
    delete pFramework;

    // return this part of the WM_QUIT message
    return static_cast<char>(msg.wParam);
}

// Message handler
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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