#include "Game/Engine/Public/EditorEngine.h"
#include "Core/Logger/Public/Logger.h"
#include "Render/RenderCore/Public/RenderThread.h"

using namespace Lumen::Game;
using namespace Lumen::Core;
using namespace Lumen::Render;

void EditorEngine::PreInit()
{
	// Launch render thread
	RenderRunnable* renderRunnable = new RenderRunnable();
	RunnableThread* renderThread = RunnableThread::Create("RenderThread", renderRunnable);
}

void EditorEngine::Init()
{
	
}

void EditorEngine::Tick()
{

}

void EditorEngine::Exit()
{

}