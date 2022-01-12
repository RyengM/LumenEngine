#pragma once

#include "Core/Common/Public/RingQueue.h"
#include "Render/RHI/Common/Public/GraphicsRHI.h"
#include "Render/RenderCore/Public/RenderContext.h"
#include <vector>
#include <functional>

using namespace Lumen::Core;

namespace Lumen::Render
{
	using LambdaFunc = std::function<void(FrameRenderContext*, GraphicsRHI*)>;

	struct RenderTask
	{
		const char* mTypeName;
		LambdaFunc mLambda;

		RenderTask(const char* name, LambdaFunc lambda) : mTypeName(name), mLambda(lambda) {}
	};

	// Global render command queue, actually a ring queue with 3 frames
	// Game thread to Render thread with three frame buffer, Game is always 1-2 frames faster than Render
	class RenderCommandQueue
	{
	public:
		static RenderCommandQueue& GetInstance();

		// Set frame number from config file
		void SetFrameNum(int num);

		bool IsFull();
		bool IsEmpty();

		// Invoked at the begin of game frame, wait until render threaed finish previous work
		// If command queue is full, ignore this frame in order to not block main thread io
		bool BeginEnqueue();
		// Invoked at the end of game frame, add command list to queue
		void EndEnqueue();
		// Invoked at the begin of render frame, wait until game thread produce task lists
		// If command queue is empty, sleep a while to save resource
		bool BeginFetch();

		// Invoked from render thread, fetch cmdlist in one frame
		void FetchCommandList(std::vector<RenderTask>& out);

		template<typename LAMBDA>
		void EnqueueRenderCommand(const char* name, LAMBDA&& lambda)
		{
			LambdaFunc func = std::move(lambda);
			mRenderCommandList.emplace_back(name, func);
		}

	private:
		RenderCommandQueue();
		~RenderCommandQueue() = default;
		RenderCommandQueue(RenderCommandQueue&) = delete;
		RenderCommandQueue& operator=(RenderCommandQueue&) = delete;

	private:
		// mFrameNum must be greater or equal to 2
		int mFrameNum = 2;
		RingQueue<std::vector<RenderTask>> mRenderCommandQueue;
		std::vector<RenderTask> mRenderCommandList;
	};

#define ENQUEUE_RENDER_COMMAND(name, lambda) RenderCommandQueue::GetInstance().EnqueueRenderCommand(name, lambda)
}