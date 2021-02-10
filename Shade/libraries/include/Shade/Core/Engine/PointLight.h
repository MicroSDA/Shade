#pragma once
#include "Shade/Core/Engine/Light.h"

namespace se
{
	class SE_API PointLight : public se::Light
	{
	public:
		PointLight();
		~PointLight();
		void SetPosition(const float& x, const float& y, const float& z);
		void SetPosition(const   glm::vec3& position);
		void SetConstant(const float& constant);
		void SetLinear(const float& linear);
		void SetQaudratic(const float& qaudratic);

		const glm::vec3& GetPosition() const;
		glm::vec3& GetPosition();
		const float& GetConstant() const;
		float& GetConstant();
		const float& GetLinear()  const;
		float& GetLinear();
		const float& GetQaudratic() const;
		float& GetQaudratic();

		virtual void OnUpdate(const se::Timer& deltaTime) override;
		virtual void Process(const se::Shader* shader) override;
	protected:
		glm::vec3 m_Position;
		float     m_Constant;
		float     m_Linear;
		float     m_Qaudratic;
		int       m_Id;
	};
}


