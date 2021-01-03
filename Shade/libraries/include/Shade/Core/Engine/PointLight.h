#pragma once
#include "Shade/Core/Engine/Light.h"

namespace se
{
	class SE_API PointLight : public se::Light
	{
	public:
		PointLight();
		~PointLight();
		inline void SetPosition(const float& x, const float& y, const float& z);
		inline void SetPosition(const   glm::vec3& position);
		inline const glm::vec3& GetPosition() const;

		inline void SetConstant(const float& constant);
		inline void SetLinear(const float& linear);
		inline void SetQaudratic(const float& qaudratic);

		inline const float& GetConstant(const float& constant) const;
		inline const float& GetLinear(const float& linear) const;
		inline const float& GetQaudratic(const float& qaudratic) const;

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


