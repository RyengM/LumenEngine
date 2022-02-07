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
        [[serialize(true)]]
        std::vector<Prefab> prefabs;

        RTTR_ENABLE(BaseObject)
    };
}