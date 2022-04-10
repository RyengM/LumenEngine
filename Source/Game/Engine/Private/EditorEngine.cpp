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
    RenderRunnable* renderRunnable = new RenderRunnable(windowInfo, &mProfileData);
    RunnableThread* renderThread = RunnableThread::Create("RenderThread", renderRunnable);
}

void EditorEngine::Init()
{
    // Load asset manager, we load all the assts now, later will only load scene assets at begining
    // CPU built-in meshes will be established here
    AssetManager::GetInstance().BuildResourceMap();

    // Build built-in meshes, its okay to pass pointer since built in mesh will not be modified
    for (auto iter : *AssetManager::GetInstance().GetBuiltInMeshMap())
    {
        Mesh* mesh = iter.second;
        ENQUEUE_RENDER_COMMAND("CreateBuiltInMesh", [mesh](RHIContext* graphicsContext) {
            graphicsContext->CreateGeometry(*mesh);
        });
    }

    // Prepare scene buffer
    mSceneBuffer = std::make_unique<VisualBuffer>("scene", 1440, 810);
    auto sceneBufferPtr = mSceneBuffer.get();
    ENQUEUE_RENDER_COMMAND("CreateSceneBuffer", [sceneBufferPtr](RHIContext* graphicsContext) {
        graphicsContext->CreateSceneBuffer(sceneBufferPtr);
    });

    // Init IO status recording and link objects associated with it
    deviceStatus = std::make_shared<DeviceStatus>();
    AssetManager::GetInstance().GetScene()->camera.deviceStatus = deviceStatus;

    // Tranfer scene data to render thread
    CreateScene();
}

void EditorEngine::Tick()
{
    high_resolution_clock::time_point beginTime = high_resolution_clock::now();
    
    // Tick all entities
    if (bPlaying)
    {
        for (auto entity : AssetManager::GetInstance().GetScene()->entities)
            entity->Tick();
    }

    // Update object constant buffer
    auto entities = AssetManager::GetInstance().GetScene()->entities;
    for (auto entityPtr : entities)
    {
        ENQUEUE_RENDER_COMMAND("UpdateObjectCB", [entityProxy = Entity(*entityPtr.get())](RHIContext* graphicsContext) {
            graphicsContext->UpdateObjectCB(entityProxy);
        });
    }

    // Update pass constant buffer
    auto camera = AssetManager::GetInstance().GetScene()->camera;
    auto light = AssetManager::GetInstance().GetScene()->light;
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
    mProfileData.gameThreadTickTime = timeInterval.count();
}

void EditorEngine::Exit()
{

}

void EditorEngine::BeginPlay()
{
    for (auto entity : AssetManager::GetInstance().GetScene()->entities)
        entity->BeginPlay();
    bPlaying = true;
}

void EditorEngine::EndPlay()
{
    bPlaying = false;

    // Reset entities
}

void EditorEngine::CreateScene()
{
    // Skybox
    {
        ShaderLab* shader = AssetManager::GetInstance().GetShaderlabByGUID(xg::Guid("5ac9d5cc-5be3-4000-8b54-cffc76be4f40"));
        ENQUEUE_RENDER_COMMAND("CreatePso", [shaderProxy = ShaderLab(*shader)](RHIContext* graphicsContext) {
            graphicsContext->CreateShaderlab(shaderProxy);
        });

        ENQUEUE_RENDER_COMMAND("CreateSkyItem", [](RHIContext* graphicsContext) {
            graphicsContext->CreateSkyItem();
        });
    }

    // Entities
    for (auto entity : AssetManager::GetInstance().GetScene()->entities)
    {
        MeshComponent* meshComponent = entity->GetMeshContainerPtr();
        Mesh* mesh = AssetManager::GetInstance().GetMeshByGUID(xg::Guid(meshComponent->meshRef.guid));
        if (mesh)
        {
            ENQUEUE_RENDER_COMMAND("CreateGeo", [meshProxy = Mesh(*mesh)](RHIContext* graphicsContext) {
                graphicsContext->CreateGeometry(meshProxy);
            });
        }

        MeshRendererComponent* meshRenderer = entity->GetMeshRenderer();
        ShaderLab* shader = AssetManager::GetInstance().GetShaderlabByGUID(xg::Guid(meshRenderer->materialRef.guid));
        if (shader)
        {
            ENQUEUE_RENDER_COMMAND("CreatePso", [shaderProxy = ShaderLab(*shader)](RHIContext* graphicsContext) {
                graphicsContext->CreateShaderlab(shaderProxy);
            });
        }

        ENQUEUE_RENDER_COMMAND("CreateRenderItem", [entityProxy = Entity(*entity.get())](RHIContext* graphicsContext) {
            graphicsContext->CreateRenderItem(entityProxy);
        });
    }
}