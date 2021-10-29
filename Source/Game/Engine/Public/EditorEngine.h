#pragma once

namespace Lumen::Game
{
	class EditorEngine
	{
	public:
		void PreInit();
		void Init();
		void Tick();
		void Exit();
	};
}