#include "Render/RenderCore/Public/RenderThread.h"
#include "Render/RHI/D3D12/Public/D3DContext.h"
#include "Render/RenderCore/Public/RenderCommand.h"
#include <chrono>

using namespace Lumen::Render;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;

RenderRunnable::RenderRunnable(const WindowInfo& windowInfo, ProfileData* profileDataPtr)
{
    profileData = profileDataPtr;
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

    // Wait for GPU fence
    mGraphicsContext->BeginFrame();

    high_resolution_clock::time_point beginTime = high_resolution_clock::now();

    // Do tasks
    {
        for (auto& task : renderCommandList)
            task.mLambda(mGraphicsContext.get());
    }

    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    microseconds timeInterval = std::chrono::duration_cast<microseconds>(endTime - beginTime);
    profileData->renderThreadTickTime = timeInterval.count();
    
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