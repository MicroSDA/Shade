#include "stdafx.h"
#include "Entity.h"

se::Entity::Entity(entt::entity handle, se::Scene* scene) :
	m_EntityHandle(handle), m_pScene(scene)
{
}

se::Entity::~Entity()
{
}
