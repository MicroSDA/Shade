#include "stdafx.h"
#include "Entity.h"

se::Entity::Entity(entt::entity handle, se::EntitiesDocker* docker) :
	m_EntityHandle(handle), m_pDocker(docker)
{
}

se::Entity::~Entity()
{
}

bool se::Entity::IsValid()
{
	if (m_pDocker != nullptr)
		return m_pDocker->GetEntities().valid(m_EntityHandle);
	else return false;
}

void se::Entity::Destroy()
{
	m_pDocker->DestroyEntity(*this);
}

se::EntitiesDocker& se::Entity::GetDocker()
{
	return *m_pDocker;
}
