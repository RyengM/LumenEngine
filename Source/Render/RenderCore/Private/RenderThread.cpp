#include "Render/RenderCore/Public/RenderThread.h"
#include "Render/RHI/D3D12/Public/D3DContext.h"
#include "Render/RenderCore/Public/RenderCommand.h"

using namespace Lumen::Render;

RenderRunnable::RenderRunnable(const WindowInfo& windowInfo)
{
    // TODO. choose backend by platform
    mGraphicsContext = std::make_unique<D3DContext>(windowInfo);
}

bool RenderRunnable::Init()
{
    return true;
}

void RenderRunnable::Run()
{
    // Wait for tasks from game thread
    if (!RenderCommandQueue::GetInstance().BeginFetch()) { Sleep(100); return; }

    // Fetch render command list
    std::vector<RenderTask> renderCommandList;
    RenderCommandQueue::GetInstance().FetchCommandList(renderCommandList);

    // Wait for GPU
    mGraphicsContext->BeginFrame();

    // Do tasks
    {
        for (auto& task : renderCommandList)
            task.mLambda(mGraphicsContext.get());
    }
    
    // Show present buffer
    mGraphicsContext->Present();

    // Add a new fence point
    mGraphicsContext->EndFrame();
}

void RenderRunnable::Stop()
{

}

void RenderRunnable::Exit()
{

}