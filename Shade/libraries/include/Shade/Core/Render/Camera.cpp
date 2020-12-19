#include "Camera.h"

se::Camera::Camera(const glm::vec3& position,
	const float& fov,
	const float& aspect,
	const float& zNear,
	const float& zFar)
{
	m_Perpective = glm::perspective(fov, aspect, zNear, zFar);
	m_Position = position;
	m_Forward = glm::vec3(0, 0, 1);
	m_Up = glm::vec3(0, 1, 0);
}

se::Camera::~Camera()
{
}
