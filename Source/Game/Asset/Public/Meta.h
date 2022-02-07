#pragma once

#include "Core/Common/Public/BaseObject.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    struct Meta : public BaseObject
    {
        Meta();

        [[serialize(true)]]
        std::string guid;

        RTTR_ENABLE(BaseObject)
    };
}