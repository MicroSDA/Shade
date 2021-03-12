#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/BoxShape.h"

namespace se
{
	class SE_API RigidBody
	{
	public:
		enum class Type
		{
			Static,
			Dynamic
		};
	public:
		RigidBody();
		~RigidBody() = default;
		RigidBody(const se::RigidBody& other) noexcept
		{
			this->m_CollisionShapes = other.m_CollisionShapes;
			this->m_Type = other.m_Type;
		};
		RigidBody& operator=(const se::RigidBody& other) noexcept
		{
			this->m_CollisionShapes = other.m_CollisionShapes;
			this->m_Type = other.m_Type;

			return *this;
		};
		RigidBody(RigidBody&& other) noexcept
		{
			this->m_CollisionShapes = std::move(other.m_CollisionShapes);
			this->m_Type = other.m_Type;
		}
		RigidBody& operator=(RigidBody&& other) noexcept
		{
			if (this != &other)
			{
				this->m_CollisionShapes = std::move(other.m_CollisionShapes);
				this->m_Type = other.m_Type;
			}
			return *this;
		}
		void AddCollisionShape(se::CollisionShape* other);
		se::CollisionData TestCollision(const se::RigidBody& other) const;
		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);

		const se::RigidBody::Type& GetType() const;
	protected:
		se::RigidBody::Type m_Type;
	private:
		mutable std::vector<se::CollisionShape*> m_CollisionShapes;
	};
}

