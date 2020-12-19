#pragma once
#include <Shade/Definitions.h>
#include <Shade/Vendors/glm/glm.hpp>
#include <Shade/Vendors/glm/gtx/transform.hpp>

namespace se {

	class SE_API Transform
	{
	public:
		Transform();
		~Transform();

		inline glm::vec3 GetPosition()                      { return m_Possition; };
		inline glm::vec3 GetRotation()                      { return m_Rotation; };
		inline glm::vec3 GetScale()                         { return m_Scale; };
		inline void SetPostition(const glm::vec3& position) { m_Possition = position; };
		inline void SetRotation(const glm::vec3& rotation)  { m_Rotation = rotation; }
		inline void SetScale(const glm::vec3& scale)        { m_Scale = scale; };
		inline glm::mat4 GetModel() const
		{
			glm::mat4 positionMatrix  = glm::translate(m_Possition);
			glm::mat4 rotationXMatrix = glm::rotate(glm::radians(m_Rotation.x), glm::vec3(1.0, 0.0, 0.0));
			glm::mat4 rotationYMatrix = glm::rotate(glm::radians(m_Rotation.y), glm::vec3(0.0, 1.0, 0.0));
			glm::mat4 rotationZMatrix = glm::rotate(glm::radians(m_Rotation.z), glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 scaleMatrix     = glm::scale(m_Scale);
			glm::mat4 rotationMatrix  = rotationXMatrix * rotationYMatrix * rotationZMatrix;
			return glm::mat4(positionMatrix * rotationMatrix * scaleMatrix);
		}
	private:
		glm::vec3 m_Possition;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}

