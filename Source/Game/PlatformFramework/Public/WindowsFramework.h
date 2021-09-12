#pragma once
#include "BaseFramework.h"
#include "Game/PlatformFramework/Public/stdafx.h"

namespace Lumen::Game
{
	class WindowsFramework : public BaseFramework
	{
	public:
		WindowsFramework(const char* name) : BaseFramework(name) {};

		virtual void OnParseCommand(const char* cmdLine) = 0;
		virtual void OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void Run() = 0;
	};
}

using namespace Lumen::Game;
int RunFramework(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, WindowsFramework* pFramework);