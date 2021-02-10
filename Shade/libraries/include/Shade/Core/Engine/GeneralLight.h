#pragma once
#include "Shade/Core/Engine/Light.h"

namespace se
{
	class SE_API GeneralLight : public se::Light
	{
	public:
		GeneralLight();
		virtual ~GeneralLight();
		void SetDirection(const float& x, const float& y, const float& z);
		void SetDirection(const glm::fvec3& direction);
		const glm::fvec3& GetDirection() const;
		glm::fvec3& GetDirection();
		
		virtual void OnUpdate(const se::Timer& deltaTime) override;
		virtual void Process(const se::Shader* shader) override;
	protected:
		glm::fvec3 m_Direction;
	private:	
	};

}


