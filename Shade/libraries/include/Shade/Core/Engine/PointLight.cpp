#include "stdafx.h"
#include "PointLight.h"
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
se::PointLight::PointLight() : se::Light(),
	m_Position(0.0f, 0.0f, 0.0f),
	m_Constant(1.0f),
	m_Linear(0.7f),
	m_Qaudratic(1.8f),
	m_Id(0) // Missing id for now
{
}

se::PointLight::~PointLight()
{
}

inline void se::PointLight::SetPosition(const float& x, const float& y, const float& z)
{
	m_Position = glm::vec3(x, y, z);
}

inline void se::PointLight::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

inline const glm::vec3& se::PointLight::GetPosition() const
{
	return m_Position;
}

inline void se::PointLight::SetConstant(const float& constant)
{
	m_Constant = constant;
}

inline void se::PointLight::SetLinear(const float& linear)
{
	m_Linear = linear;
}

inline void se::PointLight::SetQaudratic(const float& qaudratic)
{
	m_Qaudratic = qaudratic;
}

inline const float& se::PointLight::GetConstant(const float& constant) const
{
	return m_Constant;
}

inline const float& se::PointLight::GetLinear(const float& linear) const
{
	return  m_Linear;
}

inline const float& se::PointLight::GetQaudratic(const float& qaudratic) const
{
	return m_Qaudratic;
}

void se::PointLight::OnUpdate(const se::Timer& deltaTime)
{
}

void se::PointLight::Process(const se::Shader* shader)
{
	shader->SendUniform3Float("pointL.Light.ColorAmbient",     m_AmbientColor);
	shader->SendUniform3Float("pointL.Light.ColorDiffuse",     m_DiffuseColor);
	shader->SendUniform3Float("pointL.Light.ColorSpecular",    m_SpecularColor);
	shader->SendUniform3Float("pointL.Position",			   m_Position);
	shader->SendUniform1Float("pointL.Constant",			   m_Constant);
	shader->SendUniform1Float("pointL.Linear",				   m_Linear);
	shader->SendUniform1Float("pointL.Qaudratic",			   m_Qaudratic);
}
