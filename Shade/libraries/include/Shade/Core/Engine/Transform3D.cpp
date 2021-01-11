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

inline const glm::vec3& se::Transform3D::GetPosition() const
{
	return m_Possition;
}

inline const glm::fvec3& se::Transform3D::GetRotation() const
{
	return m_Rotation;
}

inline const glm::fvec3& se::Transform3D::GetScale() const
{
	return m_Scale;
}

inline void se::Transform3D::SetPostition(const glm::vec3& position)
{
	m_Possition = position;
}
inline void se::Transform3D::SetPostition(const float& x, const float& y, const float& z)
{
	m_Possition.x = x;
	m_Possition.y = y;
	m_Possition.z = z;
}
inline void se::Transform3D::SetRotation(const float& x, const float& y, const float& z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}
inline void se::Transform3D::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}
inline void se::Transform3D::SetScale(const float& x, const float& y, const float& z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}
inline void se::Transform3D::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
}