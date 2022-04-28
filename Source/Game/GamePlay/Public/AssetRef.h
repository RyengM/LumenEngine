#pragma once

#include "Core/Common/Public/BaseObject.h"

using namespace Lumen::Core;

// Reference of asset
struct AssetRef : public BaseObject
{
    AssetRef();

    [[serialize(true)]]
    std::string name;
    [[serialize(true)]]
    std::string guid;

    RTTR_ENABLE(BaseObject)
};