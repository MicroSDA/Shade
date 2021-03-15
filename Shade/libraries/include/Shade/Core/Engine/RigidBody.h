#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/MeshShape.h"

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
		virtual ~RigidBody();

		RigidBody(se::RigidBody&& other) noexcept :
			m_BodyType(se::RigidBody::Type::Dynamic)	
		{
			this->m_CollisionShapes = std::move(other.m_CollisionShapes);
			this->m_BodyType = other.m_BodyType;
		};
		RigidBody& operator=(RigidBody&& other) noexcept
		{
			if (this != &other)
			{
				this->m_CollisionShapes = std::move(other.m_CollisionShapes);
				this->m_BodyType = other.m_BodyType;
			}
			return *this;
		}

		void SetType(const se::RigidBody::Type& type);
		const se::RigidBody::Type& GetType() const;
		se::CollisionShape::CollisionData TestCollision(const glm::mat4& transform, const se::RigidBody& other, const glm::mat4& otherTransform) const;

		void AddCollider(const std::shared_ptr<se::CollisionShape>& shape); // can be const !
	protected:
	private:
		se::RigidBody::Type m_BodyType;
		std::vector<std::shared_ptr<se::CollisionShape>> m_CollisionShapes;
	};
}


