#pragma once

#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MeshRendererComponent.h"

namespace Lumen::Game
{
    // Objects make up the world, entity can attach to another entity and is made up with components
    class Entity : public BaseObject
    {
    public:
        Entity();

        virtual void BeginPlay() {};
        virtual void Tick() {};

        inline std::string GetName() const noexcept { return mName; }
        inline void SetName(std::string_view name) noexcept { mName = name; }

        inline TransformComponent* GetTransform() noexcept { return &mTransform; }

        inline MeshComponent* GetMeshContainer() noexcept {return &mMeshContainer;}
        inline void SetMeshGUID(std::string_view guid) noexcept { mMeshContainer.meshRef.guid = guid; }

        inline MeshRendererComponent* GetMeshRenderer() noexcept { return &mMeshRenderer; }
        inline void SetShaderGUID(std::string_view guid) noexcept { mMeshRenderer.materialRef.guid = guid; }

    protected:
        [[serialize(true)]]
        std::string mName;
        [[serialize(true)]]
        std::vector<Entity> mChildEntities;

        [[serialize(true)]]
        TransformComponent mTransform;

        // Fix component type now, to expand ability to use vector of pointers
        // We need to allocate specific type of memory before auto deserialize
        [[serialize(true)]]
        MeshComponent mMeshContainer;
        [[serialize(true)]]
        MeshRendererComponent mMeshRenderer;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(BaseObject)
    };
}