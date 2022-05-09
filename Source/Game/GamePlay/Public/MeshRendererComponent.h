#pragma once

#include "Component.h"
#include "Game/Asset/Public/Material.h"

namespace Lumen::Game
{
    class MeshRendererComponent : public Component
    {
    public:
        MeshRendererComponent();

    public:
        [[serialize(true)]]
        AssetRef material;

        RTTR_ENABLE(Component)
    };
}