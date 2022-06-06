#pragma once

#include "Entity.h"

namespace Lumen::Game
{
    // Entities with mesh and renderer
    class MeshEntity : public Entity
    {
    public:
        MeshEntity();
        virtual ~MeshEntity() {}

        virtual void BeginPlay() {};
        virtual void Tick() {};

        virtual MeshComponent* GetMeshContainer() const override;
        virtual MeshRendererComponent* GetMeshRenderer() const override;

        inline void SetMeshGUID(std::string_view guid) noexcept { mMeshContainer.mesh.guid = guid; }

    protected:
        [[serialize(true)]]
        MeshComponent mMeshContainer;
        [[serialize(true)]]
        MeshRendererComponent mMeshRenderer;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(Entity)
    };
}