#pragma once

#include "Game/Asset/Public/Prefab.h"
#include "Game/GamePlay/Public/Camera.h"
#include "Game/GamePlay/Public/Light.h"

namespace Lumen::Game
{
    struct Scene : public BaseObject 
    {
        Scene();
        Scene(const Scene& rhs);
        Scene(Scene&& rhs);
        
        // TODO. Settings

        [[serialize(true)]]
        Camera camera;

        [[serialize(true)]]
        DirectionalLight light;

        [[serialize(true)]]
        std::vector<Entity> entities;

        // TODO. Add prefabs to support entity group ref

        RTTR_ENABLE(BaseObject)
    };
}