#pragma once

#include "Game/Asset/Public/ShaderLabCompiler.h"
#include "Game/Asset/Public/Scene.h"
#include "Game/Asset/Public/Texture.h"
#include "Game/GamePlay/Public/Camera.h"
#include "Game/GamePlay/Public/Light.h"
#include "Core/Common/Public/Config.h"
#include "Render/RenderCore/Public/RenderThread.h"
#include "Render/RenderCore/Public/VisualBuffer.h"

#include <memory>

using namespace Lumen::Render;

namespace Lumen::Game
{
    // Engine with editor, manage all platform independent data of engine
    class EditorEngine
    {
    public:
        // Launch modules, DO NOT submit render task at preinit stage except device initialization
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
        inline VisualBuffer* GetSceneBufferPtr() const noexcept { return mSceneBuffer.get(); }

    private:
        // If editor is in playing mode, entity will not tick if beginplay is not activated
        bool bPlaying = false;
        // Config data
        Config mConfig;
        std::unique_ptr<Scene> mScene;
        std::unique_ptr<VisualBuffer> mSceneBuffer;
        // Objects for test, remove later
        std::unique_ptr<Mesh> mBox;
        std::unique_ptr<Texture> mTexture;
        std::unique_ptr<Camera> mCamera;
        std::unique_ptr<ShaderLab> mShaderLab;
        std::unique_ptr<DirectionalLight> mDirectionalLight;
    };
}