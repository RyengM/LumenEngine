#pragma once

#include "Core/Common/Public/Config.h"
#include "Game/Asset/Public/Scene.h"
#include "Render/RenderCore/Public/RenderThread.h"
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

    private:
        // If editor is in playing mode, entity will not tick if beginplay is not activated
        bool bPlaying = false;
        // Config data
        Config mConfig;
        std::unique_ptr<Scene> mScene;
    };
}