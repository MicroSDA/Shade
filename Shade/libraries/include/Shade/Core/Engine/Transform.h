#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtx/transform.hpp"

namespace se {

	class SE_API Transform
	{
	public:
		Transform();
		~Transform();

		inline const glm::vec3& GetPosition()       const               { return m_Possition; };
		inline const glm::vec3& GetRotation()       const               { return m_Rotation; };
		inline const glm::vec3& GetScale()          const               { return m_Scale; };
		inline void SetPostition(const glm::vec3& position) { m_Possition = position; };
		inline void SetPostition(const float& x, const float& y, const float& z) { m_Possition = glm::vec3(x,y,z); };
		inline void SetRotation(const glm::vec3& rotation)  { m_Rotation = rotation; }
		inline void SetScale(const glm::vec3& scale)        { m_Scale = scale; };
		inline glm::mat4 GetModel() const
		{
			glm::mat4 _PositionMatrix  = glm::translate(m_Possition);
			glm::mat4 _RotationXMatrix = glm::rotate(glm::radians(m_Rotation.x), glm::vec3(1.0, 0.0, 0.0));
			glm::mat4 _RotationYMatrix = glm::rotate(glm::radians(m_Rotation.y), glm::vec3(0.0, 1.0, 0.0));
			glm::mat4 _RotationZMatrix = glm::rotate(glm::radians(m_Rotation.z), glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 _ScaleMatrix     = glm::scale(m_Scale);
			glm::mat4 _RotationMatrix  = _RotationXMatrix * _RotationYMatrix * _RotationZMatrix;
			return glm::mat4(_PositionMatrix * _RotationMatrix * _ScaleMatrix);
		}
	private:
		glm::vec3 m_Possition;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}

