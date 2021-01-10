#include "stdafx.h"
#include "EntitiesDocker.h"
#include "Shade/Core/Engine/Entity.h"


se::EntitiesDocker::EntitiesDocker()
{
}

se::EntitiesDocker::~EntitiesDocker()
{
}

se::Entity se::EntitiesDocker::CreateEntity()
{
    return { m_Registry.create(), this };
}

entt::registry& se::EntitiesDocker::GetEntities()
{
    return m_Registry;
}
