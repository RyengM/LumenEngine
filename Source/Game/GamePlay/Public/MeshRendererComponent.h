#pragma once

#include "Component.h"

namespace Lumen::Game
{
    class MeshRendererComponent : public Component
    {
    public:
        MeshRendererComponent() = default;

    public:
        [[serialize(true)]]
        AssetRef materialRef;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(Component)
    };
}