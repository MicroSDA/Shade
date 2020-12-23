#include "stdafx.h"
#include "Camera.h"
#include "Shade/Core/Engine/WindowManager.h"
se::Camera::Camera()
{
	m_Perpective = glm::perspective(70.0f,
		(float)((float)se::WindowManager::GetWindow().Width /
			(float)se::WindowManager::GetWindow().Height),
		0.01f, 3000.0f);
	m_Position = glm::vec3(0, 0, 0);
	m_Forward = glm::vec3(0, 0, 1);
	m_Up = glm::vec3(0, 1, 0);
}

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
