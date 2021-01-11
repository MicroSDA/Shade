#include "stdafx.h"
#include "EntitiesDocker.h"
#include "Shade/Core/Engine/Entity.h"

se::EntitiesDocker::~EntitiesDocker()
{
    GetEntities().clear();
}

se::Entity se::EntitiesDocker::CreateEntity()
{
    return { m_Registry.create(), this };
}

void se::EntitiesDocker::DestroyEntity(const Entity& entity)
{
   m_Registry.destroy(entity);
}

entt::registry& se::EntitiesDocker::GetEntities()
{
    return m_Registry;
}
