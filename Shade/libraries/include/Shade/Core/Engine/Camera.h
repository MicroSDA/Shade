#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtx/transform.hpp"

namespace se
{
	class SE_API Camera
	{
	public:
		Camera();
		Camera(const glm::vec3& position,
			   const float& fov,
			   const float& aspect,
			   const float& zNear,
			   const float& zFar);
		~Camera();
		inline glm::mat4 GetView()              const { return glm::lookAt(m_Position, m_Forward, m_Up); };
		inline glm::mat4 GetProjection()        const { return m_Perpective; };
		inline glm::mat4 GetViewProjection()    const { return m_Perpective * glm::lookAt(m_Position, m_Forward, m_Up); }
		inline glm::vec3 GetForwardDirrection() const { return m_Forward; }
		inline glm::vec3 GetUpDirrection()      const { return m_Up; }
		inline glm::vec3 GetPosition()          const { return m_Position; }

		inline void MoveForward(const float& value) { m_Position += m_Forward * value; }
		inline void MoveBack(const float& value) { m_Position -= m_Forward * value; }
		inline void MoveRight(const float& value) { m_Position -= glm::cross(m_Up, m_Forward) * value; }
		inline void MoveLeft(const float& value) { m_Position += glm::cross(m_Up, m_Forward) * value; }

		// Counter clockwise issue there
		// Y
		inline void RotateYaw(float angle)
		{
			glm::mat4 rotation = glm::rotate(glm::radians(angle), UP);
			m_Forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_Forward, 0.0f)));
			m_Up = glm::vec3(glm::normalize(rotation * glm::vec4(m_Up, 0.0f)));
		}
		// X
		inline void RotatePitch(float angle)
		{
			glm::vec3 right = glm::normalize(glm::cross(m_Up, m_Forward));
			m_Forward = glm::vec3(glm::normalize(glm::rotate(glm::radians(-angle), right) * glm::vec4(m_Forward, 0.0)));
			m_Up = glm::normalize(glm::cross(m_Forward, right));
		}
		// Z
		inline void SetRoll(float angle) { /* TODO:*/ }

		void Resize();
	private:
		const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f); // Y is up
		glm::mat4 m_Perpective;
		glm::vec3 m_Position;
		glm::vec3 m_Forward;
		glm::vec3 m_Up;
		float m_Fov, m_Aspect, m_zNear, m_zFar;
	};

}

