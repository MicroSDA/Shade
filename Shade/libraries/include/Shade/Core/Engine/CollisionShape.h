#pragma once
#include"Shade/Core/CoreAPI.h"
#include "Vendors/glm/glm.hpp"

namespace se
{
	class SE_API CollisionShape
	{
	public:
		struct CollisionData
		{
			bool HasCollision	= false;
			float Depth			= 0.0f;            // Length of B - A
			//glm::vec3 A			= glm::vec3(0.0f); // Furhest point of A into B
			//glm::vec3 B			= glm::vec3(0.0f); // Furhest point of B into A
			glm::vec3 Direction = glm::vec3(0.0f); // B - Normalized
		};
		enum class Shape
		{
			Box,
			Sphere,
			Cylinder,
			Capsule,
			Plane,
			Mesh
		};
	public:
		CollisionShape(const se::CollisionShape::Shape& shape);
		virtual ~CollisionShape() = default;

		const se::CollisionShape::Shape& GetShape() const;
		virtual se::CollisionShape::CollisionData TestCollision(const glm::mat4& transform,
			const se::CollisionShape& other, const glm::mat4& otherTransform) const { return se::CollisionShape::CollisionData(); }; // void = 0 ?
		virtual glm::vec3 FindFurthestPoint(const glm::mat4& transform, const glm::vec3& direction) const { return glm::vec3(0.0f); };
	protected:
	private:
		const se::CollisionShape::Shape m_ShapeType;
	};
}
