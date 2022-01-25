#pragma once

#include "Component.h"

namespace Lumen::Game
{
    // Objects make up the world, entity can attach to another entity and is made up with components
    class Entity : public BaseObject
    {
    public:
        Entity();

        inline std::string GetName() const noexcept { return mName; }
        inline void SetName(std::string_view name) noexcept { mName = name; }

    private:
        [[serialize(true)]]
        std::string mName;
        [[serialize(true)]]
        std::shared_ptr<Entity> mOwner;
        [[serialize(true)]]
        std::vector<Component*> mComponents;
        [[serialize(true)]]
        std::vector<Entity*> mChildEntities;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(BaseObject)
    };
}