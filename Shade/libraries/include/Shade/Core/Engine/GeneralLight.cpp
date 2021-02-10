#include "stdafx.h"
#include "GeneralLight.h"

se::GeneralLight::GeneralLight() : se::Light(se::Environment::EnvironmentType::GeneralLight),
	m_Direction(0.0f, 0.0f, 1.0f)
{
}

se::GeneralLight::~GeneralLight()
{
}

void se::GeneralLight::SetDirection(const float& x, const float& y, const float& z)
{
	m_Direction = glm::vec3(x, y, z);
}

void se::GeneralLight::SetDirection(const glm::fvec3& direction)
{
	m_Direction = direction;
}

const glm::fvec3& se::GeneralLight::GetDirection() const
{
	return m_Direction;
}

glm::fvec3& se::GeneralLight::GetDirection()
{
	return const_cast<glm::fvec3&>(const_cast<const se::GeneralLight*>(this)->GetDirection());
}

void se::GeneralLight::OnUpdate(const se::Timer& deltaTime)
{
}

void se::GeneralLight::Process(const se::Shader* shader)
{
	shader->SendUniform3Float("generalL.Direction",        glm::normalize(m_Direction));
	shader->SendUniform3Float("generalL.ColorAmbient",     m_AmbientColor);
	shader->SendUniform3Float("generalL.ColorDiffuse",     m_DiffuseColor);
	shader->SendUniform3Float("generalL.ColorSpecular",    m_SpecularColor);
}
