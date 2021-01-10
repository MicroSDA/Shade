#include "stdafx.h"
#include "Entity.h"

se::Entity::Entity(entt::entity handle, se::EntitiesDocker* docker) :
	m_EntityHandle(handle), m_pDocker(docker)
{
}

se::Entity::~Entity()
{
}
