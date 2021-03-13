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
		~RigidBody() = default;
		void SetType(const se::RigidBody::Type& type);
		const se::RigidBody::Type& GetType() const;
		bool TestCollision(const glm::mat4& transform, const se::RigidBody& other, const glm::mat4& otherTransform) const;

		void AddCollider(se::CollisionShape* shape); // can be const !
	protected:
	private:
		se::RigidBody::Type m_BodyType;
		std::vector<se::CollisionShape*> m_CollisionShapes;
	};
}


