#include "App/DemoWindows/Public/DemoApp.h"

using namespace Demo;
using namespace Lumen::Game;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    LPCSTR Name = "Demo";

    return DemoWindows::RunFramework(hInstance, lpCmdLine, nShowCmd, new DemoWindows(Name));
}