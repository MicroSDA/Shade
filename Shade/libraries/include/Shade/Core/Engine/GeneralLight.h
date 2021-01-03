#pragma once
#include "Shade/Core/Engine/Light.h"

namespace se
{
	class SE_API GeneralLight : public se::Light
	{
	public:
		GeneralLight();
		virtual ~GeneralLight();
		inline void SetDirection(const float& x, const float& y, const float& z);
		inline void SetDirection(const glm::fvec3& direction);
		inline const glm::fvec3& GetDirection() const;
		

		virtual void OnUpdate(const se::Timer& deltaTime) override;
		virtual void Process(const se::Shader* shader) override;
	protected:
		glm::fvec3 m_Direction;
	private:	
	};

}


