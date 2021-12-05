#pragma once

#include "Core/Thread/Public/RunnableThread.h"
#include "Core/Logger/Public/Logger.h"

using namespace Lumen::Core;

namespace Lumen::Render
{
	class RenderRunnable : public Runnable
	{
	public:
		virtual bool Init() override;
		virtual void Run() override;
		virtual void Stop() override;
		virtual void Exit() override;
		virtual ~RenderRunnable() override {}
	};
}