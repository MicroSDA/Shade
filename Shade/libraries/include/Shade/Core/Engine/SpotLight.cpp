#include "stdafx.h"
#include "SpotLight.h"
/*  Range Constant Linear  Quadratic

	3250, 1.0,     0.0014  0.000007

	600,  1.0,     0.007   0.0002

	325,  1.0,     0.014,  0.0007

	200,  1.0,     0.022,  0.0019

	160,  1.0,     0.027,  0.0028

	100,  1.0,     0.045,  0.0075

	65,   1.0,     0.07,   0.017

	50,   1.0,     0.09,   0.032

	32,   1.0,     0.14,   0.07

	20,   1.0,     0.22,   0.20

	13,   1.0,     0.35,   0.44

	7,    1.0,     0.7,    1.8
*/
se::SpotLight::SpotLight() : se::Light(),
	m_Direction(0.0, 0.0f, 1.0f),
	m_Position(0.0f, 0.0f, 0.0f),
	m_Constant(1.0f),
	m_Linear(0.007f),
	m_Qaudratic(0.00007f),
	m_MinAngle(glm::cos(glm::radians(5.5f))),
	m_MaxAngle(glm::cos(glm::radians(7.5f))),
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
	shader->SendUniform3Float("spotL.Light.Light.Direction",        m_Direction);
	shader->SendUniform3Float("spotL.Light.Position",               m_Position);
	shader->SendUniform1Float("spotL.Light.Constant",               m_Constant);
	shader->SendUniform1Float("spotL.Light.Linear",                 m_Linear);
	shader->SendUniform1Float("spotL.Light.Qaudratic",              m_Qaudratic);
	shader->SendUniform1Float("spotL.MinAngle",                     m_MinAngle);
	shader->SendUniform1Float("spotL.MaxAngle",                     m_MaxAngle);
}
