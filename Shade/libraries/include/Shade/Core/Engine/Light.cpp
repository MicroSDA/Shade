#include "stdafx.h"
#include "Light.h"

se::Light::Light() : se::Environment(),
	m_AmbientColor(0.1, 0.1, 0.1),
	m_DiffuseColor(1.0f, 1.0f, 1.0f),
	m_SpecularColor(1.0f, 1.0f, 1.0f),
	m_ShininesStrength(1.0)
{
}

se::Light::~Light()
{
}
