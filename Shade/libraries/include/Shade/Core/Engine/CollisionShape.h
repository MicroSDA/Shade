#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glm/gtx/transform.hpp"
#include "Vendors/glm/gtx/quaternion.hpp"
#include "Vendors/glm/gtx/matrix_decompose.hpp"

namespace se
{
	struct CollisionData
	{
		bool IsColliding = false;
		glm::vec3 Dirrection; // minimum translation vector
	};

	class SE_API CollisionShape
	{
	public:
		enum class Shape
		{
			Box
		};

		CollisionShape(const CollisionShape::Shape& shape);
		virtual ~CollisionShape() { std::cout << "deleted\n"; };
		virtual se::CollisionData TestCollision(const se::CollisionShape& other) const = 0;
		virtual glm::vec3 Support(const glm::vec3& direction) const = 0;
		const se::CollisionShape::Shape& GetShape() const;

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
	protected:
		const se::CollisionShape::Shape m_Shape;

		glm::vec3 m_Position;
		glm::mat3 m_RotationScaleMatix;
		glm::mat3 m_RotationScaleMatixInversed;
	private:
	};
}