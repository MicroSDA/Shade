#include "stdafx.h"
#include "RigidBody.h"

se::RigidBody::RigidBody() :
	m_BodyType(se::RigidBody::Type::Dynamic)
{

}

void se::RigidBody::SetType(const se::RigidBody::Type& type)
{
	m_BodyType = type;
}

const se::RigidBody::Type& se::RigidBody::GetType() const
{
	return m_BodyType;
}

bool se::RigidBody::TestCollision(const glm::mat4& transform, const se::RigidBody& other, const glm::mat4& otherTransform) const
{
	for (const auto& colliderA : m_CollisionShapes)
	{
		for (const auto& colliderB : other.m_CollisionShapes)
		{
			auto result = colliderA->TestCollision(transform, *colliderB, otherTransform);
			if (result.IsCollide)
				return true;
		}
	}
	return false;
}

void se::RigidBody::AddCollider(se::CollisionShape* shape)
{
	m_CollisionShapes.push_back(shape);
}
