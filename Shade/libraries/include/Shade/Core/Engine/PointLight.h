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
		inline glm::vec3& GetPositionRef() { return m_Position; };

		inline void SetConstant(const float& constant);
		inline void SetLinear(const float& linear);
		inline void SetQaudratic(const float& qaudratic);

		inline const float& GetConstant()  const;
		inline float& GetConstantRef() { return m_Constant; };
		inline const float& GetLinear()    const;
		inline float& GetLinearRef() { return m_Linear; };
		inline const float& GetQaudratic() const;
		inline float& GetQaudraticRef() { return m_Qaudratic; };

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


