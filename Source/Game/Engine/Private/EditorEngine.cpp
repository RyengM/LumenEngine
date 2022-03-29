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
    RunnableThread* renderThread = RunnableThread::Create("RenderThread", renderRunnable);
}

void EditorEngine::Init()
{
    // Load scene
    {
        // Prepare scene buffer
        mSceneBuffer = std::make_unique<VisualBuffer>("scene", 1440, 810);
        auto sceneBufferPtr = mSceneBuffer.get();
        ENQUEUE_RENDER_COMMAND("CreateSceneBuffer", [sceneBufferPtr](RHIContext* graphicsContext) {
            graphicsContext->CreateSceneBuffer(sceneBufferPtr);
        });

        // Load mesh
        mBox = std::make_unique<Mesh>();
        mBox->name = "box";
        MeshLoader::LoadObj(mBox.get(), "../../Assets/box.obj");

        // Load shaderlab
        mShaderLab = std::make_unique<ShaderLab>();
        ShaderLabCompiler::GetInstance().Compile(mShaderLab.get(), "../../Assets/SimpleForward.shader");

        // Load camera
        mCamera = std::make_unique<Camera>(90.f, 16.f / 9.f, 0.1f, 100.f);

        // Load light
        mDirectionalLight = std::make_unique<DirectionalLight>(Vec3(0.f, 0.f, 0.f), Vec3(1.f, -1.f, 1.f), Vec3(1.f, 1.f, 1.f), Vec3(0.5f, 0.5f, 0.5f));

        // Tranfer data to render thread
        ENQUEUE_RENDER_COMMAND("CreateGeo", [meshProxy = Mesh(*mBox.get())](RHIContext* graphicsContext) {
            graphicsContext->CreateGeometry(meshProxy);
        });
        ENQUEUE_RENDER_COMMAND("CreatePso", [shaderProxy = ShaderLab(*mShaderLab.get())](RHIContext* graphicsContext) {
            graphicsContext->CreateShaderlab(shaderProxy);
        });
    }
}

void EditorEngine::Tick()
{
    // Tick all entities
    if (bPlaying)
    {
        for (auto entity : mScene->entities)
            entity.Tick();
    }

    // Update render data
    auto updatePassCBLambda = [camProxy = Camera(*mCamera.get()), lightProxy = DirectionalLight(*(mDirectionalLight.get()))](RHIContext* graphicsContext) {
        graphicsContext->UpdatePassCB(camProxy, lightProxy);
    };
    ENQUEUE_RENDER_COMMAND("UpdatePassCB", updatePassCBLambda);

    // Render scene
    uint32_t sceneWidth = mSceneBuffer->width, sceneHeight = mSceneBuffer->height;
    auto renderSceneLambda = [sceneWidth, sceneHeight](RHIContext* graphicsContext) {
        graphicsContext->RenderScene(sceneWidth, sceneHeight);
    };
    ENQUEUE_RENDER_COMMAND("RenderScene", renderSceneLambda);
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