#pragma once

#include "Core/Common/Public/Config.h"
#include "Render/RenderCore/Public/RenderContext.h"
#include <memory>

using namespace Lumen::Render;

namespace Lumen::Game
{
	// Engine with editor, manage all platform independent data of engine
	class EditorEngine
	{
	public:
		// Launch modules, DO NOT submit render task at preinit stage except device initialization
		void PreInit();
		// Load assets
		void Init();
		// Update logic and send cmd to render thread
		void Tick();
		// Exit engine
		void Exit();

		// Helper function for GUI proxy transmission
		void SubmitGUIPorxy(void* proxy);

		inline int GetCurrFrame() const noexcept { return mCurrFrame; }
		inline Config GetConfig() const noexcept { return mConfig; }

	private:
		int mCurrFrame = 0;
		// Config data
		Config mConfig;
		// Proxy data in the scene
		std::shared_ptr<RenderContext> mRenderContext;
		// Current frame proxy data produced from game thread
		FrameRenderContext mCurFrameRenderContext;
	};
}