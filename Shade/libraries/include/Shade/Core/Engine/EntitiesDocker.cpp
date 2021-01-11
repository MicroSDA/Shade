#include "stdafx.h"
#include "EntitiesDocker.h"
#include "Shade/Core/Engine/Entity.h"
#include "Shade/Core/Engine/Components.h"

se::EntitiesDocker::~EntitiesDocker()
{
    GetEntities().clear();
}

se::Entity se::EntitiesDocker::CreateEntity(const std::string& name)
{
    Entity _Entity = { m_Registry.create(), this };
    auto& _Tag = _Entity.AddComponent<se::TagComponent>();
    _Tag.Tag = (name == "Entity") ? "Entity" : name;
    return _Entity;
}

void se::EntitiesDocker::DestroyEntity(const Entity& entity)
{
   m_Registry.destroy(entity);
}

entt::registry& se::EntitiesDocker::GetEntities()
{
    return m_Registry;
}
