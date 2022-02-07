#pragma once

#include "Game/GamePlay/Public/Entity.h"

namespace Lumen::Game
{
    struct Prefab : public BaseObject
    {
        [[serialize(true)]]
        std::string name;

        [[serialize(true)]]
        std::vector<Entity> entities;

        [[setialize(true)]]
        std::vector<Prefab> prefabs;
    };
}