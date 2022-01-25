#include "Render/RenderCore/Public/RenderThread.h"
#include "Render/RHI/D3D12/Public/D3D12GraphicsRHI.h"
#include "Render/RenderCore/Public/RenderCommand.h"

using namespace Lumen::Render;

bool RenderRunnable::Init()
{
    // TODO. choose backend by platform
    mGraphicsRHI = std::make_unique<D3D12GraphicsRHI>();

    return true;
}

void RenderRunnable::Run()
{
    // If render command queue is empty, sleep a while
    if (!RenderCommandQueue::GetInstance().BeginFetch()) { Sleep(100); return; }

    // Once we get the render command list, do tasks
    std::vector<RenderTask> renderCommandList;
    RenderCommandQueue::GetInstance().FetchCommandList(renderCommandList);

    // Get current frame render context
    mRenderContext->FetchFrameRenderContext(mCurFrameRenderContext);

    // Change frame resource and wait for GPU fence
    mGraphicsRHI->NewFrame();

    for (auto& task : renderCommandList)
        task.mLambda(&mCurFrameRenderContext, mGraphicsRHI.get());

    // Swap buffer and set a new fence point
    mGraphicsRHI->EndFrame();
}

void RenderRunnable::Stop()
{

}

void RenderRunnable::Exit()
{

}

void RenderRunnable::MakeSharedRenderContext(std::shared_ptr<RenderContext> context)
{
    mRenderContext = context;
}