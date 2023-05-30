#include "Game/Engine/Public/EditorEngine.h"
#include "Render/RenderCore/Public/RenderCommand.h"
#include "Core/Logger/Public/Logger.h"
#include <chrono>

using namespace Lumen::Game;
using namespace Lumen::Core;
using namespace Lumen::Render;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;

EditorEngine::EditorEngine()
    : bPlaying(false)
    , bSwapchainResized(false)
    , bSceneResized(false)
    , mCachedSceneWidth(1440)
    , mCachedSceneHeight(810)
    , mRenderThread(nullptr)
{}

void EditorEngine::PreInit(const WindowInfo& windowInfo)
{
    SCOPE_INFO("Editor engine preInit");

    // Read config file and fill config, todo later

    // Init render command, the frame buffer size should be larger than one
    RenderCommandQueue::GetInstance().SetFrameNum(mConfig.frameBufferNum);

    // Launch render thread
    RenderRunnable* renderRunnable = new RenderRunnable(windowInfo, &mProfileData);
    mRenderThread = RunnableThread::Create("RenderThread", renderRunnable);

    // Register engine reflections that may not be auto reflected
    RegisterReflections();

    mCachedWindowInfo = windowInfo;
}

void EditorEngine::Init()
{
    SCOPE_INFO("Editor engine init");

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
    mSceneBuffer = std::make_unique<VisualBuffer>("scene", mCachedSceneWidth, mCachedSceneHeight);
    auto sceneBufferPtr = mSceneBuffer.get();
    ENQUEUE_RENDER_COMMAND("CreateSceneBuffer", [sceneBufferPtr](RHIContext* graphicsContext) {
        graphicsContext->CreateSceneBuffer(sceneBufferPtr);
    });

    // Init IO status recording and link objects associated with it
    deviceStatus = std::make_shared<DeviceStatus>();
    Camera* camera = dynamic_cast<Camera*>(AssetManager::GetInstance().GetScene()->entities[0].get());
    camera->deviceStatus = deviceStatus;
    camera->UpdateProjMatrix();
    camera->Update();

    // Tranfer scene data to render thread
    CreateScene();
}

void EditorEngine::Tick()
{
    high_resolution_clock::time_point beginTime = high_resolution_clock::now();

    // Resize scene buffer
    if (bSceneResized)
    {
        // TODO.
    }

    // Resize swapchain buffer
    if (bSwapchainResized)
    {
        ENQUEUE_RENDER_COMMAND("Resize", [this](RHIContext* graphicsContext) {
            graphicsContext->Resize(mCachedWindowInfo);
        });
        bSwapchainResized = false;
    }
    
    auto& entities = AssetManager::GetInstance().GetScene()->entities;

    // Tick all entities
    if (bPlaying)
    {
        for (int i = 0; i < entities.size(); i++)
            if (entities[i].get() && !entities[i]->IsPendingDestroy())
                entities[i]->Tick();
    }

    // Update object constant buffer, may be removed from tick with dirty flag later
    std::set<Material*> usedMaterials;
    for (int i = 0; i < entities.size(); i++)
    {
        if (!entities[i].get() || entities[i]->IsPendingDestroy())
            continue;
        if (entities[i]->GetMeshRenderer())
            if (Material* mat = AssetManager::GetInstance().GetMaterialByGUID(xg::Guid(entities[i]->GetMeshRenderer()->material.guid)))
                usedMaterials.emplace(mat);
        if (entities[i]->GetMeshContainer())
            ENQUEUE_RENDER_COMMAND("UpdateObjectCB", [entityProxy = Entity(*entities[i].get())](RHIContext* graphicsContext) {
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
    auto camera = dynamic_cast<Camera*>(entities[0].get());
    auto light = dynamic_cast<DirectionalLight*>(entities[1].get());
    auto updatePassCBLambda = [camProxy = Camera(*camera), lightProxy = DirectionalLight(*light)](RHIContext* graphicsContext) {
        graphicsContext->UpdatePassCB(camProxy, lightProxy);
    };
    ENQUEUE_RENDER_COMMAND("UpdatePassCB", updatePassCBLambda);

    // Render scene
    uint32_t sceneWidth = mSceneBuffer->width, sceneHeight = mSceneBuffer->height;
    auto renderSceneLambda = [sceneWidth, sceneHeight](RHIContext* graphicsContext) {
        graphicsContext->RenderScene(sceneWidth, sceneHeight);
    };
    ENQUEUE_RENDER_COMMAND("RenderScene", renderSceneLambda);

    // Delete pending entities
    AssetManager::GetInstance().GetScene()->DeletePendingEntities();

    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    microseconds timeInterval = std::chrono::duration_cast<microseconds>(endTime - beginTime);
    mProfileData.gameThreadTickTime = timeInterval.count();
}

void EditorEngine::Exit()
{
    mRenderThread->Exit();
    LOG_INFO("Editor engine exit");
}

void EditorEngine::OnResize(const WindowInfo& windowInfo)
{
    bSwapchainResized = true;
    mCachedWindowInfo = windowInfo;
}

void EditorEngine::BeginPlay()
{
    SCOPE_INFO("BeginePlay");

    auto& entities = AssetManager::GetInstance().GetScene()->entities;
    for (int i = 0; i < entities.size(); i++)
        if (entities[i].get() && !entities[i]->IsPendingDestroy())
            entities[i]->BeginPlay();
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
    auto& entities = AssetManager::GetInstance().GetScene()->entities;
    for (int i = 0; i < entities.size(); i++)
    {
        if (!entities[i].get() || entities[i]->IsPendingDestroy())
            continue;
        if (entities[i]->GetMeshContainer() && entities[i]->GetMeshRenderer())
        {
            std::shared_ptr<Entity>& entity = entities[i];
            ENQUEUE_RENDER_COMMAND("CreateEntity", [entity](RHIContext* graphicsContext) {
                const Entity entityProxy(*entity.get());
                const MeshComponent meshContainer(*entity->GetMeshContainer());
                const MeshRendererComponent meshRenderer(*entity->GetMeshRenderer());
                graphicsContext->CreateEntity(entityProxy, meshContainer, meshRenderer);
            });
        }
    }
}

void EditorEngine::RegisterReflections()
{
    DirectionalLight light;
}