#include "Render/RenderCore/Public/RenderCommand.h"
#include "Core/Logger/Public/Logger.h"

using namespace Lumen::Render;

RenderCommandQueue& RenderCommandQueue::GetInstance()
{
    static RenderCommandQueue instance;
    return instance;
}

RenderCommandQueue::RenderCommandQueue()
{
    mRenderCommandQueue.Reserve(mFrameNum);
}

void RenderCommandQueue::SetFrameNum(int num)
{
    assert(num > 1);
    mFrameNum = num;
    mRenderCommandQueue.Reserve(mFrameNum);
}

bool RenderCommandQueue::IsFull()
{
    // Render thread will fetch queue immediately when queue is prepared by game thread
    // Queue should be finished executed before we record new render tasks
    if (mRenderCommandQueue.Size() == (size_t)mFrameNum - 1) return true;
    return false;
}

bool RenderCommandQueue::IsEmpty()
{
    if (mRenderCommandQueue.Size() == 0) return true;
    return false;
}

bool RenderCommandQueue::BeginEnqueue()
{
    // If the queue is full, wait until render threaed finish previous work
    if (IsFull()) return false;
    mRenderCommandList.clear();
    return true;
}

bool RenderCommandQueue::BeginFetch()
{
    // If the queue is empty, wait until game thread produce task lists
    if (IsEmpty()) return false;
    return true;
}

void RenderCommandQueue::EndEnqueue()
{
    mRenderCommandQueue.Emplace(mRenderCommandList);
}

void RenderCommandQueue::FetchCommandList(std::vector<RenderTask>& out)
{
    out = std::move(mRenderCommandQueue.Front());
    mRenderCommandQueue.Pop();
}