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
        AssetRef shaderlabRef;

        [[serialize(true)]]
        Material material;

        RTTR_ENABLE(Component)
    };
}