#pragma once

#include "Component.h"
#include "Core/Math/Public/Vector.h"

namespace Lumen::Game
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent() =  default;

    public:
        [[serialize(true)]]
        Vec4 position;
        [[serialize(true)]]
        Vec4 rotation;
        [[serialize(true)]]
        Vec4 scale;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(Component)
    };
}