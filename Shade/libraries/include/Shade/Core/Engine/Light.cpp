#include "stdafx.h"
#include "Light.h"

se::Light::Light(const se::Environment::EnvironmentType& type) : se::Environment(type),
	m_AmbientColor(0.1, 0.1, 0.1),
	m_DiffuseColor(1.0f, 1.0f, 1.0f),
	m_SpecularColor(1.0f, 1.0f, 1.0f)
{
}

se::Light::~Light()
{
}
