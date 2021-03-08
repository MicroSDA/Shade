#pragma once
#include "Shade/Core/CoreAPI.h"
#include <Vendors/glm/glm.hpp>
#include <Vendors/glm/gtc/type_ptr.hpp>

namespace se
{
	struct CollisionData
	{
		bool  IsCollision = false;
		float Distance = 0.0f;
	};
	class SE_API Collider3D
	{
	public:
		enum class Type
		{
			Point,
			AABB,
			Sphere,
			Plot
		};

		Collider3D(const se::Collider3D::Type& type);
		virtual ~Collider3D() = default;
		virtual void SetTranslate(const glm::vec3& translate) = 0;
		virtual const CollisionData CheckCollision(const se::Collider3D& other) = 0;
		const se::Collider3D::Type& GetType() const;
	protected:
		const se::Collider3D::Type m_Type;
		glm::vec3 m_Translate;
	private:
	};
}