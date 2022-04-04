#pragma once

#include "Entity.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    struct DirectionalLight : public Entity
    {
        [[serialize(true)]]
        Vec3 strength = Vec3(0, 0, 0);

        DirectionalLight();
        DirectionalLight(const Vec3& pos, const Vec3& direction, const Vec3& scale, const Vec3& strength) : strength(strength)
        {
            mTransform.position = pos;
            mTransform.rotation = direction;
            mTransform.scale = scale;
        }

        inline Vec3 GetPosition() const noexcept { return mTransform.position; }
        inline Vec3 GetDirection() const noexcept { return mTransform.rotation; }

        RTTR_ENABLE(Entity)
    };
}