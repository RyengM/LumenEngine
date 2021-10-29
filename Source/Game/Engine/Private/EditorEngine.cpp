#include "Game/Engine/Public/EditorEngine.h"
#include "Render/RenderCore/Public/RenderCommand.h"
#include "Core/Logger/Public/Logger.h"

using namespace Lumen::Game;
using namespace Lumen::Core;
using namespace Lumen::Render;

void EditorEngine::PreInit()
{

}

void EditorEngine::Init()
{
	
}

void EditorEngine::Tick()
{
	ENQUEUE_RENDER_COMMAND("BeginFrame", [](SceneContext* sceneContext, RHICommandListBase* cmdList)
	{
		// Invoke render thread function
	});
}

void EditorEngine::Exit()
{

}