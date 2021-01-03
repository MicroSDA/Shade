#include "stdafx.h"
#include "GeneralLight.h"

se::GeneralLight::GeneralLight() : se::Light(),
	m_Direction(0.0f, 0.0f, 1.0f)
{
}

se::GeneralLight::~GeneralLight()
{
}

inline void se::GeneralLight::SetDirection(const float& x, const float& y, const float& z)
{
	m_Direction = glm::vec3(x, y, z);
}

inline void se::GeneralLight::SetDirection(const glm::fvec3& direction)
{
	m_Direction = direction;
}

inline const glm::fvec3& se::GeneralLight::GetDirection() const
{
	return m_Direction;
}

void se::GeneralLight::OnUpdate(const se::Timer& deltaTime)
{
}

void se::GeneralLight::Process(const se::Shader* shader)
{
	shader->SendUniform3Float("generalL.Direction",        m_Direction);
	shader->SendUniform3Float("generalL.ColorAmbient",     m_AmbientColor);
	shader->SendUniform3Float("generalL.ColorDiffuse",     m_DiffuseColor);
	shader->SendUniform3Float("generalL.ColorSpecular",    m_SpecularColor);
	shader->SendUniform1Float("generalL.ShininesStrength", m_ShininesStrength);
}
