#pragma once

#include "Game/PlatformFramework/Windows/Public/WindowsFramework.h"

namespace Demo
{
    using namespace Lumen::Game;

    class DemoWindows : public WindowsFramework
    {
    public:
        DemoWindows(const wchar_t* name) : WindowsFramework(name) {};
    };
}