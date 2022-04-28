#pragma once

#include "Component.h"
#include "AssetRef.h"
#include "Game/Asset/Public/Mesh.h"

namespace Lumen::Game
{
    class MeshComponent : public Component
    {
    public:
        MeshComponent();

    public:
        [[serialize(true)]]
        AssetRef mesh;

        RTTR_ENABLE(Component)
    };
}