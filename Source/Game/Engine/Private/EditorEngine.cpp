#include "Game/Engine/Public/EditorEngine.h"
#include "Render/RenderCore/Public/RenderCommand.h"
#include "Core/Logger/Public/Logger.h"
#include <chrono>

using namespace Lumen::Game;
using namespace Lumen::Core;
using namespace Lumen::Render;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;

void EditorEngine::PreInit(const WindowInfo& windowInfo)
{
    // Read config file and fill config, todo later

    // Init render command, the frame buffer size should be larger than one
    RenderCommandQueue::GetInstance().SetFrameNum(mConfig.frameBufferNum);

    // Launch render thread
    RenderRunnable* renderRunnable = new RenderRunnable(windowInfo, &profileData);
    RunnableThread* renderThread = RunnableThread::Create("RenderThread", renderRunnable);
}

void EditorEngine::Init()
{
    // Load asset manager, we load all the assts now, later will only load scene assets at begining
    mAssetManager = std::make_unique<AssetManager>();
    mAssetManager->BuildResourceMap();

    // Prepare scene buffer
    mSceneBuffer = std::make_unique<VisualBuffer>("scene", 1440, 810);
    auto sceneBufferPtr = mSceneBuffer.get();
    ENQUEUE_RENDER_COMMAND("CreateSceneBuffer", [sceneBufferPtr](RHIContext* graphicsContext) {
        graphicsContext->CreateSceneBuffer(sceneBufferPtr);
    });

    // Tranfer scene data to render thread
    CreateScene();
}

void EditorEngine::Tick()
{
    high_resolution_clock::time_point beginTime = high_resolution_clock::now();
    
    // Tick all entities
    if (bPlaying)
    {
        for (auto entity : mAssetManager->GetScene()->entities)
            entity.Tick();
    }

    // Update object constant buffer
    auto entities = mAssetManager->GetScene()->entities;
    ENQUEUE_RENDER_COMMAND("UpdateObjectCB", [entities](RHIContext* graphicsContext) {
        graphicsContext->UpdateObjectCB(entities);
    });

    // Update pass constant buffer
    auto camera = mAssetManager->GetScene()->camera;
    auto light = mAssetManager->GetScene()->light;
    auto updatePassCBLambda = [camProxy = Camera(camera), lightProxy = DirectionalLight(light)](RHIContext* graphicsContext) {
        graphicsContext->UpdatePassCB(camProxy, lightProxy);
    };
    ENQUEUE_RENDER_COMMAND("UpdatePassCB", updatePassCBLambda);

    // Render scene
    uint32_t sceneWidth = mSceneBuffer->width, sceneHeight = mSceneBuffer->height;
    auto renderSceneLambda = [sceneWidth, sceneHeight](RHIContext* graphicsContext) {
        graphicsContext->RenderScene(sceneWidth, sceneHeight);
    };
    ENQUEUE_RENDER_COMMAND("RenderScene", renderSceneLambda);

    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    microseconds timeInterval = std::chrono::duration_cast<microseconds>(endTime - beginTime);
    profileData.gameThreadTickTime = timeInterval.count();
}

void EditorEngine::Exit()
{

}

void EditorEngine::BeginPlay()
{
    for (auto entity : mAssetManager->GetScene()->entities)
        entity.BeginPlay();
    bPlaying = true;
}

void EditorEngine::EndPlay()
{
    bPlaying = false;

    // Reset entities
}

void EditorEngine::CreateScene()
{
    for (Entity& entity : mAssetManager->GetScene()->entities)
    {
        MeshComponent* meshComponent = entity.GetMeshContainer();
        Mesh* mesh = mAssetManager->GetMeshByGUID(xg::Guid(meshComponent->meshRef.guid));
        ENQUEUE_RENDER_COMMAND("CreateGeo", [meshProxy = Mesh(*mesh)](RHIContext* graphicsContext) {
            graphicsContext->CreateGeometry(meshProxy);
        });

        MeshRendererComponent* meshRenderer = entity.GetMeshRenderer();
        ShaderLab* shader = mAssetManager->GetShaderlabByGUID(xg::Guid(meshRenderer->materialRef.guid));
        ENQUEUE_RENDER_COMMAND("CreatePso", [shaderProxy = ShaderLab(*shader)](RHIContext* graphicsContext) {
            graphicsContext->CreateShaderlab(shaderProxy);
        });

        ENQUEUE_RENDER_COMMAND("CreateRenderItem", [entity](RHIContext* graphicsContext) {
            graphicsContext->CreateRenderItem(const_cast<Entity&>(entity));
        });
    }
}