#pragma once

#include "Core/Thread/Public/RunnableThread.h"
#include "Core/Logger/Public/Logger.h"
#include "Render/RHI/Common/Public/GraphicsRHI.h"
#include "Render/RenderCore/Public/RenderContext.h"

using namespace Lumen::Core;

namespace Lumen::Render
{
	class RenderRunnable : public Runnable
	{
	public:
		virtual bool Init() override;
		// Consume command and execute them
		virtual void Run() override;
		virtual void Stop() override;
		virtual void Exit() override;
		virtual ~RenderRunnable() override {}

		void MakeSharedRenderContext(std::shared_ptr<RenderContext> context);

	private:
		std::unique_ptr<GraphicsRHI> mGraphicsRHI;
		// Shared from game thread, contains all the proxies for render
		std::shared_ptr<RenderContext> mRenderContext;
		// Current frame proxy data consumed by render thread
		FrameRenderContext mCurFrameRenderContext;
	};
}