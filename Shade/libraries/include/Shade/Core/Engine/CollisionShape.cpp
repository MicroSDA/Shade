#include "stdafx.h"
#include "CollisionShape.h"

se::CollisionShape::CollisionShape(const CollisionShape::Shape& shape)
	:m_Shape(shape)
{
	m_Position = glm::vec3(0, 0, 0);
	m_RotationScaleMatix = glm::toMat3(glm::quat(glm::vec3(0, 0, 0)));
	m_RotationScaleMatixInversed = glm::inverse(m_RotationScaleMatix);
}

const se::CollisionShape::Shape& se::CollisionShape::GetShape() const
{
	return m_Shape;
}

void se::CollisionShape::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void se::CollisionShape::SetRotation(const glm::vec3& rotation)
{
	m_RotationScaleMatix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(glm::quat(rotation)) * glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
	m_RotationScaleMatixInversed = glm::inverse(m_RotationScaleMatix);
}
