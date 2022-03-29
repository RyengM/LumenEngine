#pragma once

#include "Component.h"
#include "Core/Math/Public/MathUtil.h"

namespace Lumen::Game
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent() =  default;

    public:
        [[serialize(true)]]
        Vec3 position;
        [[serialize(true)]]
        Vec3 rotation;
        [[serialize(true)]]
        Vec3 scale;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(Component)
    };
}