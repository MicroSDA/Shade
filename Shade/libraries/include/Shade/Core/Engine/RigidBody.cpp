#include "stdafx.h"
#include "RigidBody.h"

se::RigidBody::RigidBody() :
	m_BodyType(se::RigidBody::Type::Dynamic)
{

}
se::RigidBody::~RigidBody()
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

se::CollisionShape::CollisionData se::RigidBody::TestCollision(const glm::mat4& transform, const se::RigidBody& other, const glm::mat4& otherTransform) const
{
	for (const auto& colliderA : m_CollisionShapes)
	{
		for (const auto& colliderB : other.m_CollisionShapes)
		{
			auto result = colliderA->TestCollision(transform, *colliderB, otherTransform);
			if (result.HasCollision)
				return result;
		}
	}
	return { false };
}

void se::RigidBody::AddCollider(const std::shared_ptr<se::CollisionShape>& shape)
{
	m_CollisionShapes.push_back(shape);
}
