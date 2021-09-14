#pragma once

namespace Lumen::Game
{
	class Launcher
	{
	public:
		void PreInit();
		void Init();
		void Tick();
		void Exit();
	};
}