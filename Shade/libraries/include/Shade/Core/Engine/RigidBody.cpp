#include "stdafx.h"
#include "RigidBody.h"

se::RigidBody::RigidBody() :
	m_Type(se::RigidBody::Type::Dynamic)
{
}

void se::RigidBody::AddCollisionShape(se::CollisionShape* other)
{
	if(other->GetShape() == se::CollisionShape::Shape::Box)
		m_CollisionShapes.push_back(static_cast<se::BoxShape*>(other));
}

se::CollisionData se::RigidBody::TestCollision(const se::RigidBody& other) const
{
	for (int i = 0; i < m_CollisionShapes.size(); i++)
	{
		for (int j = 0; j < other.m_CollisionShapes.size(); j++)
		{
			auto result = m_CollisionShapes[i]->TestCollision(*other.m_CollisionShapes[j]);
			if (result.IsColliding)
			{
				return result;
			}
		}
	}

	return se::CollisionData{ false, glm::vec3(0.f, 0.f, 0.f)};
}

void se::RigidBody::SetPosition(const glm::vec3& position)
{
	for (auto& collider : m_CollisionShapes)
	{
		collider->SetPosition(position);
	}
}

void se::RigidBody::SetRotation(const glm::vec3& rotation)
{
	for (auto& collider : m_CollisionShapes)
	{
		collider->SetRotation(rotation);
	}
}

const se::RigidBody::Type& se::RigidBody::GetType() const
{
	return m_Type;
}
