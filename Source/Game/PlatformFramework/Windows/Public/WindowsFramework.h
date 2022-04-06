#pragma once

#include "Game/Engine/Public/BaseFramework.h"
#include "Game/PlatformFramework/Windows/Public/ImguiManagerDx12.h"
#include <memory>

namespace Lumen::Game
{
    // Provide Win32 backend with DX12
    // Include GUI interface which ref data from engine
    class WindowsFramework : public BaseFramework
    {
    public:
        WindowsFramework(const wchar_t* name) : BaseFramework(name) {};
        static int RunFramework(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, WindowsFramework* pFramework);

    protected:
        bool InitMainWindow();
        // Break loop if return false
        bool HandleIO();
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        // Do some work with GUI and d3d12 backend
        void InitUI();
        void UpdateUI();
        void Clean();
        // GUI interaction
        void EnterDictRecur(AssetTreeNode* node);
        void UpdateGuiWindow();

    public:
        // Imgui settings
        ImguiManagerDx12    mImguiManager;

        // Win32 settings
        HINSTANCE           mhAppInst = nullptr;            // Application instance handle
        WNDCLASS            mWndClass;
        WindowInfo          mWindowInfo;
    };

    // Record the address of imgui manager in framework, used for WinProc
    static ImguiManagerDx12* gImguiManager = nullptr;
}