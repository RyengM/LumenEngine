#pragma once

namespace Lumen::Game
{
    template<EntityType T>
    T* Scene::SpawnEntity(std::string_view entityName)
    {
		std::shared_ptr<T> entity = std::make_shared<T>();
		entity->SetName(entityName);

		if (entity->GetMeshContainer())
			CreateEntityOnRender(entity);

		entityMap.emplace(entity->GetGuid(), entities.size());
		entities.emplace_back(std::move(entity));

		return dynamic_cast<T*>(entities.back().get());
    }
}