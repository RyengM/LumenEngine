#pragma once

#include "Game/Asset/Public/AssetManager.h"
#include "Core/Common/Public/Config.h"
#include "Render/RenderCore/Public/RenderThread.h"
#include "Render/RenderCore/Public/VisualBuffer.h"

using namespace Lumen::Render;

namespace Lumen::Game
{
    // Engine with editor, manage all platform independent data of engine
    class EditorEngine
    {
    public:
        EditorEngine();

        // Launch modules
        void PreInit(const WindowInfo& windowInfo);
        // Load assets
        void Init();
        // Update logic and send cmd to render thread
        void Tick();
        // Exit engine
        void Exit();
        // Resize buffer
        void OnResize(const WindowInfo& windowInfo);

        void BeginPlay();
        void EndPlay();

        Config GetConfig() const noexcept { return mConfig; }
        ProfileData* GetProfileData() noexcept { return &mProfileData; }
        VisualBuffer* GetSceneBufferPtr() const noexcept { return mSceneBuffer.get(); }

        void SetResizedSceneInfo(float sceneWidth, float sceneHeight) { mCachedSceneWidth = sceneWidth; mCachedSceneHeight = sceneHeight; bSceneResized = true; }
        void GetCachedSceneInfo(float& outSceneWidth, float& outSceneHeight) { outSceneWidth = mCachedSceneWidth; outSceneHeight = mCachedSceneHeight; }

    private:
        // Use scene data from asset manager to build gpu resource
        void CreateScene();
        // Register engine reflections that may not be auto reflected
        void RegisterReflections();

    public:
        // Record device IO status
        std::shared_ptr<DeviceStatus> deviceStatus;

    private:
        // If editor is in playing mode, entity will not tick if beginplay is not activated
        bool bPlaying : 1;
        // If editor window is resized
        bool bSwapchainResized : 1;
        // If scene is resized
        bool bSceneResized : 1;

        // Cached scene size, TODO. if this size changed, scene buffer will be resized
        float mCachedSceneWidth;
        float mCachedSceneHeight;

        // Config data
        Config mConfig;
        // Profile data
        ProfileData mProfileData;
        // Scene display buffer
        std::unique_ptr<VisualBuffer> mSceneBuffer;
        // Render thread handle
        RunnableThread* mRenderThread;
        // Cached editor window info, if this info changed, swapchain will be resized
        WindowInfo mCachedWindowInfo;
    };
}