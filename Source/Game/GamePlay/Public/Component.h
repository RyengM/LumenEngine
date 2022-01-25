#pragma once

#include "Core/Common/Public/BaseObject.h"
#include "Core/Common/Public/Guid.hpp"

using namespace Lumen::Core;

namespace Lumen::Game
{
    // Reference of asset
    struct AssetRef : public BaseObject
    {
        [[serialize(true)]]
        std::string guid;
        std::shared_ptr<BaseObject> ref;
    };

    // Base class of all components
    // Components cannot be put into world directly, it must be attached to an actor as root
    class Component : public BaseObject
    {
    public:
        Component();

        inline std::string GetName() const noexcept { return mName; }
        inline void SetName(std::string_view name) noexcept { mName = name; }

    private:
        [[serialize(true)]]
        std::string mName;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(BaseObject)
    };
}