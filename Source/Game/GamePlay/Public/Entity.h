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
        virtual ~Entity() {}

        virtual void BeginPlay() {};
        virtual void Tick() {};

        // Entity will not be destroied immediately, will be destroied at end of game tick
        void Destroy();

        // Try to get mesh and renderer
        virtual MeshComponent* GetMeshContainer() const { return nullptr; }
        virtual MeshRendererComponent* GetMeshRenderer() const { return nullptr; }

        inline std::string GetName() const noexcept { return mName; }
        inline void SetName(std::string_view name) noexcept { mName = name; }

        // Used for data transmission between threads, object type should be const
        inline TransformComponent GetTransform() const noexcept { return mTransform; }

        inline xg::Guid GetGuid() const noexcept { return mGuid; }

        inline bool IsPendingDestroy() const noexcept { return bPendingDestroy; }

    protected:
        [[serialize(true)]]
        std::string mClassName;

        [[serialize(true)]]
        std::string mName;

        [[serialize(true)]]
        TransformComponent mTransform;

        // Each entity instance in the scene will have a unique id, no not need to be serialized
        xg::Guid mGuid;

        // If this actor will be destroied at the end of this frame
        bool bPendingDestroy = false;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(BaseObject)
    };
}