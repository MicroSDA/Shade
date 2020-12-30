#include "stdafx.h"
#include "GeneralLight.h"

se::GeneralLight::GeneralLight() : se::Light(),
	m_Direction(0.0f, 0.0f, 1.0f)
{
}

se::GeneralLight::~GeneralLight()
{
}

void se::GeneralLight::OnUpdate(const se::Timer& deltaTime)
{
}

void se::GeneralLight::Process(const se::Shader* shader)
{
	shader->SendUniform3Float("generalL.direction",        m_Direction);
	shader->SendUniform3Float("generalL.colorAmbient",     m_AmbientColor);
	shader->SendUniform3Float("generalL.colorDiffuse",     m_DiffuseColor);
	shader->SendUniform3Float("generalL.colorSpecular",    m_SpecularColor);
	shader->SendUniform1Float("generalL.shininesStrength", m_ShininesStrength);
}
