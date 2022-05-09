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
        std::string guid = iter.first;
        Mesh* mesh = iter.second;
        auto lambda = [mesh, guid](RHIContext* graphicsContext) {
            graphicsContext->CreateGeometry(*mesh, guid);
        };
        ENQUEUE_RENDER_COMMAND("CreateBuiltInMesh", lambda);
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

    // Update object constant buffer, may be removed from tick with dirty flag later
    auto entities = AssetManager::GetInstance().GetScene()->entities;
    std::set<Material*> usedMaterials;
    for (auto entityPtr : entities)
    {
        if (Material* mat = AssetManager::GetInstance().GetMaterialByGUID(xg::Guid(entityPtr->GetMeshRendererPtr()->material.guid)))
            usedMaterials.emplace(mat);
        ENQUEUE_RENDER_COMMAND("UpdateObjectCB", [entityProxy = Entity(*entityPtr.get())](RHIContext* graphicsContext) {
            graphicsContext->UpdateObjectCB(entityProxy);
        });
    }
    for (auto mat : usedMaterials)
    {
        // Update material buffer with data from editor
        if (!mat->bOffsetMapInitialized) // Initialize property offset at first time
        {
            ShaderLab* shader = AssetManager::GetInstance().GetShaderlabByGUID(xg::Guid(mat->shaderlab.guid));
            mat->InitBuffer(shader);
        }
        mat->UpdateBuffer();
        // Transport data to render side
        ENQUEUE_RENDER_COMMAND("UpdateMaterialCB", [materialProxy = Material(*mat)](RHIContext* graphicsContext) {
            graphicsContext->UpdateMaterialCB(materialProxy);
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
    // Skybox, will be combined in entities later
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
        ENQUEUE_RENDER_COMMAND("CreateEntity", [entityProxy = Entity(*entity.get())](RHIContext* graphicsContext) {
            graphicsContext->CreateEntity(entityProxy);
        });
    }
}