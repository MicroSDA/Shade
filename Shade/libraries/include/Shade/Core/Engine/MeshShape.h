#pragma once
#include "Shade/Core/Engine/CollisionShape.h"

namespace se
{
	class SE_API MeshShape : public se::CollisionShape
	{
	public:
		MeshShape();
		~MeshShape() = default;
		void AddVertex(const glm::vec3& vertex);
		// Inherited via CollisionShape
		virtual se::CollisionShape::CollisionData TestCollision(
			const glm::mat4& transform,
			const se::CollisionShape& other, 
			const glm::mat4& otherTransform) const override; // void = 0 ?
		virtual glm::vec3 FindFurthestPoint(const glm::mat4& transform, const glm::vec3& direction) const override;
	private:
		std::vector<glm::vec3> m_Vertices;
	};
}