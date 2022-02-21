#pragma once

#include "Game/Engine/Public/EditorEngine.h"

namespace Lumen::Game
{
    // Platform independent parts, for OS related should be implemented in specific implementation inherit from this class
    class BaseFramework
    {
    public:
        BaseFramework(const wchar_t* name) : mName(name) {}
        virtual ~BaseFramework() {}

        // Launch modules
        inline void PreInit(const WindowInfo& windowInfo) { mEngine.PreInit(windowInfo); }
        // Load assets
        inline void Init() { mEngine.Init(); }              
        inline void Tick() { mEngine.Tick(); }
        inline void Exit() { mEngine.Exit(); }

        inline void BeginPlay() { mEngine.BeginPlay(); }
        inline void EndPlay() { mEngine.EndPlay(); }

    public:
        const wchar_t* mName;
        EditorEngine mEngine;
    };
}