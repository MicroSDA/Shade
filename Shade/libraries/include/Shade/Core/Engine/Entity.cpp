#include "Entity.h"

se::Entity::Entity(entt::entity handl, se::Scene* scene):
	m_EntityHandl(handl), m_pScene(scene)
{
}

se::Entity::~Entity()
{
}
