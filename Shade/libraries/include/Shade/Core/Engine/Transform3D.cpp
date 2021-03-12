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
	glm::mat4 RoataionMatrix = glm::toMat4(glm::quat((m_Rotation))); // m_Rotation to radians
	return glm::translate(glm::mat4(1.0f), m_Possition) * RoataionMatrix * glm::scale(glm::mat4(1.0f), m_Scale);
}
