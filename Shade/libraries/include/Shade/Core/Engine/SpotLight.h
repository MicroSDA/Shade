#pragma once
#include "Shade/Core/Engine/Light.h"

namespace se
{
	class SE_API SpotLight :public se::Light
	{
	public:
		SpotLight();
		~SpotLight();

		 void SetPosition(const float& x, const float& y, const float& z);
		 void SetPosition(const   glm::vec3& position);
		 const glm::vec3& GetPosition() const;
		 void SetDirection(const float& x, const float& y, const float& z);
		 void SetDirection(const glm::vec3& direction);
		 void SetMinAngle(const float& angle);
		 void SetMaxAngle(const float& angle);
		 const float& GetMinAngle() const;
		 const float& GetMaxAngle() const;
		 const glm::fvec3& GetDirection() const;

		 void SetConstant(const float& constant);
		 void SetLinear(const float& linear);
		 void SetQaudratic(const float& qaudratic);

		 const float& GetConstant() const;
		 const float& GetLinear() const;
		 const float& GetQaudratic() const;

		virtual void OnUpdate(const se::Timer& deltaTime) override;
		virtual void Process(const se::Shader* shader) override;
	private:
		glm::fvec3 m_Direction;
		glm::fvec3 m_Position;
		float      m_Constant;
		float      m_Linear;
		float      m_Qaudratic;
		float      m_MinAngle;
		float      m_MaxAngle;
		int        m_Id;
	};

}

