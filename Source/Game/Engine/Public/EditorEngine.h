#pragma once

namespace Lumen::Game
{
	class EditorEngine
	{
	public:
		// Launch modules
		void PreInit();
		// Load assets
		void Init();
		// Update logic and send cmd to render thread
		void Tick();
		// Exit engine
		void Exit();
	};
}