#pragma once

#include "Game/Asset/Public/Prefab.h"
#include "Game/GamePlay/Public/Camera.h"
#include "Game/GamePlay/Public/Light.h"

// It seems std::vector<std::shared_ptr<T>> cannot be parsed by USRefl correctly now. Try fix later

namespace Lumen::Game
{
    struct Scene : public BaseObject
    {
        Scene();
        
        // TODO. Settings

        [[serialize(true)]]
        Camera camera;

        [[serialize(true)]]
        DirectionalLight light;

        [[serialize(true)]]
        std::vector<std::shared_ptr<Entity>> entities;

        // TODO. Add prefabs to support entity group ref

        RTTR_ENABLE(BaseObject)
    };
}