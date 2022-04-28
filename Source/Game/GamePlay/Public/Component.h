#pragma once

#include "Core/Common/Public/BaseObject.h"
#include "Core/Common/Public/Guid.hpp"

using namespace Lumen::Core;

namespace Lumen::Game
{
    // Base class of all components
    // Components cannot be put into world directly, it must be attached to an actor as root
    struct Component : public BaseObject
    {
        Component();

        RTTR_ENABLE(BaseObject)
    };
}