#include "stdafx.h"
#include "Light.h"

se::Light::Light(const se::Environment::Type& type) : se::Environment(type),
	m_AmbientColor(0.1, 0.1, 0.1),
	m_DiffuseColor(1.0f, 1.0f, 1.0f),
	m_SpecularColor(1.0f, 1.0f, 1.0f)
{
}

se::Light::~Light()
{
}

void se::Light::SetAmbientColor(const float& r, const float& g, const float& b)
{
	m_AmbientColor = glm::vec3(r, g, b);
}

void se::Light::SetDiffuseColor(const float& r, const float& g, const float& b)
{
	m_DiffuseColor = glm::vec3(r, g, b);
}

void se::Light::SetSpecularColor(const float& r, const float& g, const float& b)
{
	m_SpecularColor = glm::vec3(r, g, b);
}

void se::Light::SetAmbientColor(const glm::vec3& color)
{
	m_AmbientColor = color;
}

void se::Light::SetDiffuseColor(const glm::vec3& color)
{
	m_DiffuseColor = color;
}

void se::Light::SetSpecularColor(const glm::vec3& color)
{
	m_SpecularColor = color;
}

const glm::vec3& se::Light::GetAmbientColor() const
{
	return m_AmbientColor;
}

const glm::vec3& se::Light::GetDiffuseColor() const
{
	return m_DiffuseColor;
}

const glm::vec3& se::Light::GetSpecularColor() const
{
	return m_SpecularColor;
}

glm::vec3& se::Light::GetAmbientColor()
{
	return const_cast<glm::vec3&>(const_cast<const se::Light*>(this)->GetAmbientColor());
}

glm::vec3& se::Light::GetDiffuseColor()
{
	return const_cast<glm::vec3&>(const_cast<const se::Light*>(this)->GetDiffuseColor());
}

glm::vec3& se::Light::GetSpecularColor()
{
	return const_cast<glm::vec3&>(const_cast<const se::Light*>(this)->GetSpecularColor());
}
