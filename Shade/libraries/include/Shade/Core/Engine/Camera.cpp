#include "stdafx.h"
#include "Camera.h"
#include "Shade/Core/Engine/WindowManager.h"
se::Camera::Camera():
	m_Fov(45.0f), m_Aspect(
		(float)(se::WindowManager::GetWindow().Width) / 
		(float)(se::WindowManager::GetWindow().Height))
, m_zNear(0.1f), m_zFar(3000.0f)
{
	m_Perpective = glm::perspective(glm::radians(m_Fov), m_Aspect, m_zNear, m_zFar);
	m_Position = glm::vec3(0, 0, 0);
	m_Forward = glm::vec3(0, 0, 1); // - Z
	m_Up = glm::vec3(0, 1, 0);

}

se::Camera::Camera(const glm::vec3& position,
	const float& fov,
	const float& aspect,
	const float& zNear,
	const float& zFar)
{
	m_Fov    = fov;
	m_Aspect = aspect;
	m_zNear  = zNear;
	m_zFar   = zFar;

	m_Perpective = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
	m_Position = position;
	m_Forward = glm::vec3(0, 0, 1); // - Z
	m_Up = glm::vec3(0, 1, 0);

}

se::Camera::~Camera()
{
}

void se::Camera::Resize()
{
	m_Aspect = (float)se::WindowManager::GetWindow().Width / (float)se::WindowManager::GetWindow().Height;
	m_Perpective = glm::perspective(glm::radians(m_Fov), m_Aspect, m_zNear, m_zFar);
	//TODO Zoom
}
