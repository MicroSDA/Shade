#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/AABB3D.h"

namespace se
{
	class SE_API RigidBody3D
	{
	public:
		RigidBody3D(const se::Collider3D::Type& type);
		virtual ~RigidBody3D() = default;
		void SetTranslate(const glm::vec3& translate);
		const se::CollisionData CheckCollision(const se::RigidBody3D& other);

		const glm::vec3& GetDirection() const;
		const glm::vec3& GetSpeed()     const;
	private:
		std::vector<se::Collider3D*> m_Colliders;
		glm::vec3 m_Translate;
		glm::vec3 m_Direction;
		glm::vec3 m_Speed;
	};
}