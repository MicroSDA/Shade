#pragma once

#include "Shade/Core/Engine/Collider3D.h"

namespace se
{
	class SE_API AABB3D : public se::Collider3D
	{
	public:
		AABB3D(const glm::vec3& min, const glm::vec3& max);
		virtual ~AABB3D() = default;
		// Inherited via Collider3D
		virtual const CollisionData CheckCollision(const se::Collider3D& other) override;
		// Inherited via Collider3D
		virtual void SetTranslate(const glm::vec3& translate) override;

		const glm::vec3 GetMin() const;
		const glm::vec3 GetMax() const;
	protected:
		const CollisionData GetAABBCollision(const se::AABB3D& other);
	private:
		glm::vec3 m_Min;
		glm::vec3 m_Max;
	};
}