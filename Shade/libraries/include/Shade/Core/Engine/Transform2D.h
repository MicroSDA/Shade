#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtx/transform.hpp"

namespace se
{
	class SE_API Transform2D
	{
	public:
		Transform2D();
		~Transform2D();

		inline void SetPostition(const float& x, const float& y);
		inline void SetPostition(const glm::vec2& position);
		inline void SetRotation(const float& x, const float& y);
		inline void SetRotation(const glm::vec2& rotation);
		inline void SetSize(const float& x, const float& y);
		inline void SetSize(const glm::vec2& scale);
		inline void SetScale(const float& x, const float& y);
		inline void SetScale(const glm::vec2& scale);

		inline const glm::vec2& GetPosition() const;
		inline const glm::vec2& GetRotation() const;
		inline const glm::vec2& GetScale()    const;
		inline const glm::vec2 GetSize()    const;

		inline const glm::mat4 GetModel()    const;
	private:
		glm::vec2 m_Possition;
		glm::vec2 m_Rotation;
		glm::vec2 m_Scale;
	};

}

