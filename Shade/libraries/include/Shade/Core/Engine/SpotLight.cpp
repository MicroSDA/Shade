#include "stdafx.h"
#include "SpotLight.h"

se::SpotLight::SpotLight() : se::Light(),
	m_Direction(0.0, 0.0f, 1.0f),
	m_Position(0.0f, 0.0f, -5.0f),
	m_Constant(1),
	m_Linear(0.027),
	m_Qaudratic(0.0028),
	m_MinAngle(glm::cos(glm::radians(5.5))),
	m_MaxAngle(glm::cos(glm::radians(7.5))),
	m_Id(0)
{
}

se::SpotLight::~SpotLight()
{
}

inline void se::SpotLight::SetPosition(const float& x, const float& y, const float& z)
{
	m_Position = glm::vec3(z, y, z);
}

inline void se::SpotLight::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

inline const glm::vec3& se::SpotLight::GetPosition() const
{
	return m_Position;
}

inline void se::SpotLight::SetDirection(const float& x, const float& y, const float& z)
{
	m_Direction = glm::vec3(x, y, z);
}

inline void se::SpotLight::SetDirection(const glm::vec3& direction)
{
	m_Direction = direction;
}

inline void se::SpotLight::SetMinAngle(const float& angle)
{
	m_MinAngle = angle;
}

inline void se::SpotLight::SetMaxAngle(const float& angle)
{
	m_MaxAngle = angle;
}

inline const float& se::SpotLight::GetMinAngle() const
{
	return m_MinAngle;
}

inline const float& se::SpotLight::GetMaxAngle() const
{
	return m_MaxAngle;
}

inline const glm::fvec3& se::SpotLight::GetDirection() const
{
	return m_Direction;
}

void se::SpotLight::OnUpdate(const se::Timer& deltaTime)
{
}

void se::SpotLight::Process(const se::Shader* shader) 
{
	shader->SendUniform3Float("spotL.Light.Light.ColorAmbient",	    m_AmbientColor);
	shader->SendUniform3Float("spotL.Light.Light.ColorDiffuse",	    m_DiffuseColor);
	shader->SendUniform3Float("spotL.Light.Light.ColorSpecular",    m_SpecularColor);
	shader->SendUniform1Float("spotL.Light.Light.ShininesStrength", m_ShininesStrength);
	shader->SendUniform3Float("spotL.Light.Light.Direction",        m_Direction);
	shader->SendUniform3Float("spotL.Light.Position",               m_Position);
	shader->SendUniform1Float("spotL.Light.Constant",               m_Constant);
	shader->SendUniform1Float("spotL.Light.Linear",                 m_Linear);
	shader->SendUniform1Float("spotL.Light.Qaudratic",              m_Qaudratic);
	shader->SendUniform1Float("spotL.MinAngle",                     m_MinAngle);
	shader->SendUniform1Float("spotL.MaxAngle",                     m_MaxAngle);
}
