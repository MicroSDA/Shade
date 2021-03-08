#include "stdafx.h"
#include "AABB3D.h"

se::AABB3D::AABB3D(const glm::vec3& min, const glm::vec3& max) : se::Collider3D(se::Collider3D::Type::AABB),
	m_Min(min), m_Max(max)
{
}

const se::CollisionData se::AABB3D::CheckCollision(const se::Collider3D& other)
{
	switch (other.GetType())
	{
	case se::Collider3D::Type::AABB: return GetAABBCollision(static_cast<const se::AABB3D&>(other));
	default:
		return CollisionData();
		break;
	}
}

const glm::vec3 se::AABB3D::GetMin() const
{
	return m_Min + m_Translate;
}

const glm::vec3 se::AABB3D::GetMax() const
{
	return m_Max + m_Translate;
}

const se::CollisionData se::AABB3D::GetAABBCollision(const se::AABB3D& other)
{
	glm::vec3 dist_1 = other.GetMin() - this->GetMax();
	glm::vec3 dist_2 = this->GetMin() - other.GetMax();
	glm::vec3 total_dist = glm::max(dist_1, dist_2);

	float max_distance = total_dist[0];
	for (auto i = 0; i < 3; i++)
		if (total_dist[i] > max_distance)
			max_distance = total_dist[i];

	return CollisionData { max_distance <= 0, max_distance };
}

void se::AABB3D::SetTranslate(const glm::vec3& translate)
{
	m_Translate = translate;
}
