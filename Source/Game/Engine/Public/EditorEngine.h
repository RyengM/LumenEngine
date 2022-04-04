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
        // Launch modules
        void PreInit(const WindowInfo& windowInfo);
        // Load assets
        void Init();
        // Update logic and send cmd to render thread
        void Tick();
        // Exit engine
        void Exit();

        void BeginPlay();
        void EndPlay();

        inline Config GetConfig() const noexcept { return mConfig; }
        inline ProfileData* GetProfileData() noexcept { return &profileData; }
        inline Scene* GetScene() noexcept { return mAssetManager->GetScene(); }
        inline VisualBuffer* GetSceneBufferPtr() const noexcept { return mSceneBuffer.get(); }

    private:
        // Use scene data from asset manager to build gpu resource
        void CreateScene();

    private:
        // If editor is in playing mode, entity will not tick if beginplay is not activated
        bool bPlaying = false;
        // Config data
        Config mConfig;
        // Profile data
        ProfileData profileData;
        // Scene display buffer
        std::unique_ptr<VisualBuffer> mSceneBuffer;
        // Asset data
        std::unique_ptr<AssetManager> mAssetManager;
    };
}