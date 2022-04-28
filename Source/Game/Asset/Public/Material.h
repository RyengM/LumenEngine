#pragma once

#include "Core/Common/Public/BaseObject.h"
#include "Game/GamePlay/Public/AssetRef.h"
#include "Game/Asset/Public/ShaderLab.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    struct Material : public BaseObject
    {
        Material();

        std::string name;

        [[serialize(true)]]
        AssetRef shaderlab;

        [[serialize(true)]]
        AssetRef diffuseTexture;

        RTTR_ENABLE(BaseObject)
    };
}