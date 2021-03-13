#include "stdafx.h"
#include "MeshShape.h"
#include "Shade/Core/Engine/GJK.h"
se::MeshShape::MeshShape() : 
	se::CollisionShape(se::CollisionShape::Shape::Mesh)
{

}

void se::MeshShape::AddVertex(const glm::vec3& vertex)
{
	m_Vertices.emplace_back(vertex);
}

se::CollisionShape::CollisionData se::MeshShape::TestCollision(const glm::mat4& transform,
	const se::CollisionShape& other, const glm::mat4& otherTransform) const
{
	if(se::algo::GJK(*this, transform, other, otherTransform))
		return se::CollisionShape::CollisionData { true };
	else
		return se::CollisionShape::CollisionData { false };
}

glm::vec3 se::MeshShape::FindFurthestPoint(const glm::mat4& transform, const glm::vec3& direction) const
{
	glm::vec3 maxPoint;
	float     maxDistance = -FLT_MAX;

	for (auto vertex : m_Vertices) { // const can be removed
		vertex = glm::vec3(glm::vec4(vertex, 1) * glm::transpose(transform));

		float distance = glm::dot(vertex, direction);
		if (distance > maxDistance) {
			maxDistance = distance;
			maxPoint = vertex;
		}
	}
	return maxPoint;
}
