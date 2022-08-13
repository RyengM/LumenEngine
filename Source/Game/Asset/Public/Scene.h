#pragma once

#include "Game/Asset/Public/Prefab.h"
#include "Game/GamePlay/Public/Camera.h"
#include "Game/GamePlay/Public/Light.h"

// It seems std::vector<std::shared_ptr<T>> cannot be parsed by USRefl correctly now. Try fix later

namespace Lumen::Game
{
    template<typename T>
    concept EntityType = std::is_base_of<Entity, T>::value;

    struct Scene : public BaseObject
    {
        Scene();

        // Create an entity by editor reflection
        Entity* CreateEntity(std::string_view className);
        // Update entity data binding in render thread
        void UpdateEntity(Entity* entity);
        // Trigger at end of frame
        void DeletePendingEntities();
        // Clear empty entities
        void SortEntityList();

        // Create an entity by entity type
        template<EntityType T>
        T* SpawnEntity(std::string_view entityName);
        
        // TODO. Settings

        [[serialize(true)]]
        std::vector<std::shared_ptr<Entity>> entities;

        // Helper structure for entity search
        std::unordered_map<xg::Guid, size_t> entityMap;

        // The index is used for avoiding name duplication
        // TODO. use a better way to manage index to avoid name duplication
        uint32_t nameIndex = 0;

    private:
        void CreateEntityOnRender(std::shared_ptr<Entity> entity);

        RTTR_ENABLE(BaseObject)
    };
}

#include "Details/Scene.inl"