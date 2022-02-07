#pragma once

#include "Component.h"
#include "Game/Asset/Public/Mesh.h"

namespace Lumen::Game
{
    class MeshComponent : public Component
    {
    public:
        MeshComponent() = default;

    public:
        [[serialize(true)]]
        AssetRef meshRef;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(Component)
    };
}