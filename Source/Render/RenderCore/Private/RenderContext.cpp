#include "Render/RenderCore/Public/RenderContext.h"

using namespace Lumen::Render;

RenderContext::RenderContext(int frameNum)
{
    //mFrameNum = frameNum;
    mRenderContext.Reserve(frameNum);
}

void RenderContext::EnqueueFrameRenderContext(FrameRenderContext&& context)
{
    mRenderContext.Emplace(std::move(context));
}

void RenderContext::FetchFrameRenderContext(FrameRenderContext& out)
{
    out = std::move(mRenderContext.Front());
    mRenderContext.Pop();
}