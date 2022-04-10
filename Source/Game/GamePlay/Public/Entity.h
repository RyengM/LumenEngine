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

        inline std::string GetEntityClassName() const noexcept { return mClassName; }
        inline std::string GetName() const noexcept { return mName; }
        inline void SetName(std::string_view name) noexcept { mName = name; }

        // Used for data transmission between threads, object type should be const
        inline TransformComponent GetTransform() const noexcept { return mTransform; }
        // Used for UI interaction, to modify data directly, object type must be pointer
        inline TransformComponent* GetTransformPtr() noexcept { return &mTransform; }

        inline MeshComponent GetMeshContainer() const noexcept {return mMeshContainer;}
        inline MeshComponent* GetMeshContainerPtr() noexcept {return &mMeshContainer;}
        inline void SetMeshGUID(std::string_view guid) noexcept { mMeshContainer.meshRef.guid = guid; }

        inline MeshRendererComponent* GetMeshRenderer() noexcept { return &mMeshRenderer; }
        inline void SetShaderGUID(std::string_view guid) noexcept { mMeshRenderer.materialRef.guid = guid; }

        inline xg::Guid GetGuid() const noexcept { return mGuid; }

    protected:
        [[serialize(true)]]
        std::string mClassName = "Entity";

        [[serialize(true)]]
        std::string mName;

        [[serialize(true)]]
        TransformComponent mTransform;
        [[serialize(true)]]
        MeshComponent mMeshContainer;
        [[serialize(true)]]
        MeshRendererComponent mMeshRenderer;

        // Each entity instance in the scene will have a unique id, no not need to be serialized
        xg::Guid mGuid;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(BaseObject)
    };
}