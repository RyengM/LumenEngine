#include "Game/Engine/Public/EditorEngine.h"
#include "Render/RenderCore/Public/RenderCommand.h"
#include "Core/Logger/Public/Logger.h"
#include "Game/Asset/Public/Serializer.h"
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

    // Load scene
    {
        // Load scene
        Scene* scene = mAssetManager->GetScene();
        //Entity box;
        //box.SetName("box");
        //box.SetMeshGUID("fbcc47a7-c788-4222-8f6d-ec8c86c283c8");
        //box.SetShaderGUID("2beb9da1-9752-4012-95f3-eb14e00140de");
        //scene->entities.emplace_back(box);
        //scene->light = DirectionalLight(Vec3(0.f, 0.f, 0.f), Vec3(1.f, -1.f, 1.f), Vec3(1.f, 1.f, 1.f), Vec3(0.5f, 0.5f, 0.5f));
        //scene->camera = Camera(90.f, 16.f / 9.f, 0.1f, 100.f);
        //scene->camera.SetPos(Vec3(- 6.f, 6.f, -6.f));
        //Serializer::GetInstance().Serialize(scene, "../../Assets/Scene/simpleScene.scene");
        Serializer::GetInstance().Deserialize(scene, "../../Assets/Scene/simpleScene.scene");
        scene->camera.UpdateProjMatrix();
        scene->camera.Update();

        // Tranfer data to render thread
        CreateScene();
    }
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

    // Update render data
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
    }
}