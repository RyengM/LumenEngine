#pragma once

#include "Game/Asset/Public/Prefab.h"

namespace Lumen::Game
{
    struct Scene : public BaseObject 
    {
        Scene() = default;
        
        // TODO. Settings

        [[serialize(true)]]
        std::vector<Entity> entities;

        // TODO. Add prefabs to support entity group ref

        RTTR_ENABLE(BaseObject)
    };
}