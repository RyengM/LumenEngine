#pragma once

#include "Core/Common/Public/BaseObject.h"
#include "Game/Asset/Public/ShaderLab.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    struct Material : public BaseObject
    {
        Material();

        std::string name;

        [[serialize(true)]]
        std::string diffuseTextureGuid;

        RTTR_ENABLE(BaseObject)
    };
}