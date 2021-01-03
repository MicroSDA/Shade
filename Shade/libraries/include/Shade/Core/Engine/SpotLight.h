#pragma once
#include "Shade/Core/Engine/Light.h"

namespace se
{
	class SE_API SpotLight :public se::Light
	{
	public:
		SpotLight();
		~SpotLight();

		inline void SetPosition(const float& x, const float& y, const float& z);
		inline void SetPosition(const   glm::vec3& position);
		inline const glm::vec3& GetPosition() const;
		inline void SetDirection(const float& x, const float& y, const float& z);
		inline void SetDirection(const glm::vec3& direction);
		inline void SetMinAngle(const float& angle);
		inline void SetMaxAngle(const float& angle);
		inline const float& GetMinAngle() const;
		inline const float& GetMaxAngle() const;
		inline const glm::fvec3& GetDirection() const;

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

