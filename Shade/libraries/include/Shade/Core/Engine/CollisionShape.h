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
			bool IsCollide      = false;
			glm::vec3 Direction = glm::vec3(0.0f);
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

