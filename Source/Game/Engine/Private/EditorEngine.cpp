#include "Game/Engine/Public/EditorEngine.h"
#include "Core/Logger/Public/Logger.h"
#include "Render/RenderCore/Public/RenderCommand.h"

using namespace Lumen::Game;
using namespace Lumen::Core;
using namespace Lumen::Render;

void EditorEngine::PreInit(const WindowInfo& windowInfo)
{
    // Read config file and fill config, todo later

    // Init render command, the frame buffer size should be larger than one
    RenderCommandQueue::GetInstance().SetFrameNum(mConfig.frameBufferNum);

    // Launch render thread
    RenderRunnable* renderRunnable = new RenderRunnable(windowInfo);
    //renderRunnable->MakeSharedRenderContext(mRenderContext);
    RunnableThread* renderThread = RunnableThread::Create("RenderThread", renderRunnable);
}

void EditorEngine::Init()
{
    // Load scene and upload info to render context

}

void EditorEngine::Tick()
{
    // Tick all entities
    if (bPlaying)
    {
        for (auto entity : mScene->entities)
            entity.Tick();
    }

    // Enqueue render cmdlist
    ENQUEUE_RENDER_COMMAND("Clear", [](RHIContext* graphicsContext) {
        RHICommandBuffer* cmdBuffer = graphicsContext->RequestCmdBuffer(EContextType::Graphics, "ClearBuffer");

        cmdBuffer->ClearRenderTarget(graphicsContext->GetBackBuffer(), graphicsContext->GetBackBufferView(), Vec4(1, 0, 0, 1));

        graphicsContext->ExecuteCmdBuffer(cmdBuffer);
        graphicsContext->ReleaseCmdBuffer(cmdBuffer);
    });
}

void EditorEngine::Exit()
{

}

void EditorEngine::BeginPlay()
{
    for (auto entity : mScene->entities)
        entity.BeginPlay();
    bPlaying = true;
}

void EditorEngine::EndPlay()
{
    bPlaying = false;

    // Reset entities
}

void EditorEngine::SubmitGUIPorxy(void* proxy)
{
    /*mCurFrameRenderContext.guiProxies.clear();
    mCurFrameRenderContext.guiProxies.emplace_back(proxy);*/
}