#pragma once

#include "Core/Common/Public/BaseObject.h"
#include "Game/Asset/Public/ShaderLab.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    struct Material : public BaseObject
    {
        [[serialize(true)]]
        std::string shaderLabGuid;
    };

    class MaterialLoader
    {
    public:
        static void LoadMaterial(Material* mat, std::string_view sourceFile) {};
    };
}