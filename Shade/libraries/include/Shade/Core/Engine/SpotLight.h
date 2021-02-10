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
		 void SetDirection(const float& x, const float& y, const float& z);
		 void SetDirection(const glm::vec3& direction);
		 void SetMinAngle(const float& angle);
		 void SetMaxAngle(const float& angle);
		 void SetConstant(const float& constant);
		 void SetLinear(const float& linear);
		 void SetQaudratic(const float& qaudratic);

		 const glm::vec3& GetPosition() const;
		 glm::vec3& GetPosition();
		
		 const float& GetMinAngle() const;
		 float& GetMinAngle();
		 const float& GetMaxAngle() const;
		 float& GetMaxAngle();
		 const glm::fvec3& GetDirection() const;
		 glm::fvec3& GetDirection();

		 const float& GetConstant() const;
		 float& GetConstant();
		 const float& GetLinear() const;
		 float& GetLinear();
		 const float& GetQaudratic() const;
		 float& GetQaudratic();

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

