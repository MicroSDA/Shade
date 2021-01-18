#include "stdafx.h"
#include "Transform3D.h"

se::Transform3D::Transform3D():
	m_Possition(0.0f, 0.0f, 0.0f),
	m_Rotation(0.0f, 0.0f, 0.0f),
	m_Scale(1.0f, 1.0f, 1.0f)
{
}

se::Transform3D::~Transform3D()
{
}

glm::mat4 se::Transform3D::GetModelMatrix() const
{
	glm::mat4 _PositionMatrix = glm::translate(m_Possition);
	glm::mat4 _RotationXMatrix = glm::rotate(glm::radians(m_Rotation.x), glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 _RotationYMatrix = glm::rotate(glm::radians(m_Rotation.y), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 _RotationZMatrix = glm::rotate(glm::radians(m_Rotation.z), glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 _ScaleMatrix = glm::scale(m_Scale);
	glm::mat4 _RotationMatrix = _RotationXMatrix * _RotationYMatrix * _RotationZMatrix;
	return glm::mat4(_PositionMatrix * _RotationMatrix * _ScaleMatrix);
}