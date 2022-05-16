#pragma once

#include "Core/Common/Public/BaseObject.h"
#include "Game/GamePlay/Public/AssetRef.h"
#include "Game/Asset/Public/ShaderLab.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    struct PropertyList : public BaseObject
    {
        PropertyList();

        // @string: property name, string: tex guid
        [[serialize(true)]]
        std::unordered_map<std::string, AssetRef> texMap;
        [[serialize(true)]]
        std::unordered_map<std::string, int> integerMap;
        [[serialize(true)]]
        std::unordered_map<std::string, float> floatMap;
        [[serialize(true)]]
        std::unordered_map<std::string, Vec4> colorMap;

        RTTR_ENABLE(BaseObject)
    };

    struct Material : public BaseObject
    {
        Material();
        Material(const Material& rhs);
        Material(Material&& rhs);
        ~Material();

        // Fill offsetmap by shaderlab property layout and allocate buffer
        void InitBuffer(ShaderLab* shader);
        // Update buffer by propertyList reflected in editor
        void UpdateBuffer();

        std::string name;
        std::string path;
        std::string guid;

        [[serialize(true)]]
        AssetRef shaderlab;

        [[serialize(true)]]
        PropertyList propertyList;

        // Size of property list
        uint32_t propertyListSize = 0;

        // Helper structure to fast find offset of property
        std::unordered_map<std::string, uint32_t> propertyOffsetMap;
        bool bOffsetMapInitialized = false;

        // Actual storage of property data
        uint8_t* buffer;

        RTTR_ENABLE(BaseObject)
    };
}