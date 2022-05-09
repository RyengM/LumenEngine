#pragma once

#include "Core/Common/Public/BaseObject.h"

using namespace Lumen::Core;

// Reference of asset
struct AssetRef : public BaseObject
{
    AssetRef();
    AssetRef(std::string_view name, std::string_view guid) : name(name), guid(guid) {}

    [[serialize(true)]]
    std::string guid;
    [[serialize(true)]]
    std::string name;

    RTTR_ENABLE(BaseObject)
};