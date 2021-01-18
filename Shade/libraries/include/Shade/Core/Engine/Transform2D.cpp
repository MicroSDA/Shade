#include "stdafx.h"
#include "Transform2D.h"
#include "Shade/Core/Engine/WindowManager.h"

se::Transform2D::Transform2D() :
	m_Possition(0.0f, 0.0f),
	m_Rotation(0.0f, 0.0f),
	m_Scale(1.0f, 1.0f)
{
}

se::Transform2D::~Transform2D()
{

}

void se::Transform2D::SetSize(const float& x, const float& y)
{

	m_Scale.x = x / static_cast<float>(se::WindowManager::GetWindow().Width);
	m_Scale.y = y / static_cast<float>(se::WindowManager::GetWindow().Height);
}
void se::Transform2D::SetSize(const glm::vec2& scale)
{
	m_Scale.x = scale.x / static_cast<float>(se::WindowManager::GetWindow().Width);
	m_Scale.y = scale.y / static_cast<float>(se::WindowManager::GetWindow().Height);
}

const glm::vec2 se::Transform2D::GetSize() const
{
	return glm::vec2(
		m_Scale.x * static_cast<float>(se::WindowManager::GetWindow().Width),
		m_Scale.y * static_cast<float>(se::WindowManager::GetWindow().Height)
	);
}

const glm::mat4 se::Transform2D::GetModelMatrix() const
{
	glm::mat4 _PositionMatrix = glm::translate(glm::vec3(m_Possition, 0.0f));
	glm::mat4 _RotationXMatrix = glm::rotate(glm::radians(m_Rotation.x), glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 _RotationYMatrix = glm::rotate(glm::radians(m_Rotation.y), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 _RotationZMatrix = glm::rotate(glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 _ScaleMatrix = glm::scale(glm::vec3(m_Scale, 0.0f));
	glm::mat4 _RotationMatrix = _RotationXMatrix * _RotationYMatrix * _RotationZMatrix;
	return glm::mat4(_PositionMatrix * _RotationMatrix * _ScaleMatrix);
}
