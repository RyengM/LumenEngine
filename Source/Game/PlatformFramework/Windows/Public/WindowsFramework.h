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
	};
}

using namespace Lumen::Game;
int RunFramework(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, WindowsFramework* pFramework);