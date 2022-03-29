#pragma once

#include "Entity.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    struct DirectionalLight : public Entity
    {
        Vec3 strength = Vec3(0, 0, 0);

        DirectionalLight(const Vec3& pos, const Vec3& direction, const Vec3& scale, const Vec3& strength) : strength(strength)
        {
            transform.position = pos;
            transform.rotation = direction;
            transform.scale = scale;
        }

        inline Vec3 GetPosition() const noexcept { return transform.position; }
        inline Vec3 GetDirection() const noexcept { return transform.rotation; }
    };
}