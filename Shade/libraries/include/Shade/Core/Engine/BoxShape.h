#pragma once
#include "Shade/Core/Engine/CollisionShape.h"

namespace se
{
	class SE_API BoxShape : public se::CollisionShape
	{
	public:
		BoxShape(const glm::vec3& min, const glm::vec3& max);
		~BoxShape() = default;
		se::CollisionData TestCollision(const se::CollisionShape& other) const override;
	protected:
		
	private:
		glm::vec3 Support(const glm::vec3& direction) const override;
		glm::vec3 m_MinExt;
		glm::vec3 m_MaxExt;
	
		void Simplex3(glm::vec3& A, glm::vec3& B, glm::vec3& C, glm::vec3& D, glm::vec3& direction, int& simplex_dimension) const;
		bool Simplex4(glm::vec3& A, glm::vec3& B, glm::vec3& C, glm::vec3& D, glm::vec3& direction, int& simplex_dimension) const;
		glm::vec3 EPA(glm::vec3& A, glm::vec3& B, glm::vec3& C, glm::vec3& D, const se::BoxShape& other) const;

		se::CollisionData BoxCollisionTest(const se::BoxShape& other) const;

		// Inherited via CollisionShape
		//virtual se::CollisionData TestCollision(const se::CollisionShape& other) const override;
	};
}