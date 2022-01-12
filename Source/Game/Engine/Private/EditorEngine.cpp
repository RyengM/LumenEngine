#include "Game/Engine/Public/EditorEngine.h"
#include "Core/Logger/Public/Logger.h"
#include "Render/RenderCore/Public/RenderThread.h"
#include "Render/RenderCore/Public/RenderCommand.h"

using namespace Lumen::Game;
using namespace Lumen::Core;
using namespace Lumen::Render;

void EditorEngine::PreInit()
{
	// Read config file and fill config, todo later

	// Init render command, the frame buffer size should be larger than one
	RenderCommandQueue::GetInstance().SetFrameNum(mConfig.frameBufferNum);

	// Alloc memory for render context
	mRenderContext = std::make_shared<RenderContext>(mConfig.frameBufferNum);

	// Launch render thread
	RenderRunnable* renderRunnable = new RenderRunnable();
	renderRunnable->MakeSharedRenderContext(mRenderContext);
	RunnableThread* renderThread = RunnableThread::Create("RenderThread", renderRunnable);

	// We regard preinit as the first frame
	mCurrFrame = (mCurrFrame + 1) % mConfig.frameBufferNum;
	mRenderContext->EnqueueFrameRenderContext(std::move(mCurFrameRenderContext));
}

void EditorEngine::Init()
{
	// We regard init as the second frame
	mCurrFrame = (mCurrFrame + 1) % mConfig.frameBufferNum;
	mRenderContext->EnqueueFrameRenderContext(std::move(mCurFrameRenderContext));
}

void EditorEngine::Tick()
{
	mCurrFrame = (mCurrFrame + 1) % mConfig.frameBufferNum;
	mRenderContext->EnqueueFrameRenderContext(std::move(mCurFrameRenderContext));
}

void EditorEngine::Exit()
{

}

void EditorEngine::SubmitGUIPorxy(void* proxy)
{
	mCurFrameRenderContext.guiProxies.clear();
	mCurFrameRenderContext.guiProxies.emplace_back(proxy);
}