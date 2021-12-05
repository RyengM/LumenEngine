#pragma once

#include "Game/Engine/Public/BaseFramework.h"
#include "Game/PlatformFramework/Windows/Public/stdafx.h"

namespace Lumen::Game
{
	// Provide Win32 backend
	class WindowsFramework : public BaseFramework
	{
	public:
		WindowsFramework(const char* name) : BaseFramework(name) {};
		static int RunFramework(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, WindowsFramework* pFramework);

	protected:
		bool InitMainWindow();
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HINSTANCE mhAppInst = nullptr;			// Application instance handle
		HWND      mhMainWnd = nullptr;			// Main window handle
		int		  mClientWidth = 800;
		int		  mClientHeight = 600;
	};
}