#include "stdafx.h"
#include "RigidBody3D.h"

se::RigidBody3D::RigidBody3D(const se::Collider3D::Type& type)
{
	switch (type)
	{
	case se::Collider3D::Type::AABB:
		m_Colliders.push_back(new se::AABB3D(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 1.0f,  1.0f,  -1.0f)));
		m_Colliders.push_back(new se::AABB3D(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3( 1.0f,  1.0f,   1.0f)));
		m_Colliders.push_back(new se::AABB3D(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(-1.0f,  1.0f,  -1.0f)));

		m_Colliders.push_back(new se::AABB3D(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f,  1.0f, -1.0f)));
		m_Colliders.push_back(new se::AABB3D(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(1.0f,  1.0f,  1.0f)));
		m_Colliders.push_back(new se::AABB3D(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, -1.0f,  1.0f)));
		break;
	default:
		break;
	}
}

void se::RigidBody3D::SetTranslate(const glm::vec3& translate)
{
	glm::vec3 pointA, pointB;
	if (m_Translate != translate)
	{
		if (m_Translate.x == translate.x)
		{
			pointA.x = 0.0f; pointB.x = 0.0f;
		}
		else
		{
			pointA.x = m_Translate.x; pointB.x = translate.x;
		}

		if (m_Translate.y == translate.y)
		{
			pointA.y = 0.0f; pointB.y = 0.0f;
		}
		else
		{
			pointA.y = m_Translate.y; pointB.y = translate.y;
		}

		if (m_Translate.z == translate.z)
		{
			pointA.z = 0.0f; pointB.z = 0.0f;
		}
		else
		{
			pointA.z = m_Translate.z; pointB.z = translate.z;
		}

		m_Direction   = glm::normalize(pointA - pointB);
	}
	else
	{
		m_Direction   = glm::vec3(0, 0, 0);
	}

	m_Translate   = translate;

	for (auto& collider : m_Colliders)
	{
		collider->SetTranslate(m_Translate);
	}
}

const se::CollisionData se::RigidBody3D::CheckCollision(const se::RigidBody3D& other)
{
	for (auto i = 0; i < m_Colliders.size(); i ++)
	{
		for (auto j = 0; j < other.m_Colliders.size(); j++)
		{
			auto data = m_Colliders[i]->CheckCollision(*other.m_Colliders[j]);
			
			if (data.IsCollision)
				return data;
		}
	}
	return se::CollisionData {false};
}

const glm::vec3& se::RigidBody3D::GetDirection() const
{
	return m_Direction;
}

const glm::vec3& se::RigidBody3D::GetSpeed() const
{
	return m_Speed;
}
