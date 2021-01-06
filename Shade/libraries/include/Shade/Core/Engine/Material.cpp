#include "stdafx.h"
#include "Material.h"

se::Material::Material() :
    m_AmbientColor(0.1f, 0.1f, 0.1f),
    m_DiffuseColor(1.0f, 1.0f, 1.0f),
    m_SpecularColor(1.0f, 1.0f, 1.0f),
    m_TransparentMask(0.0f, 0.0f, 0.0f),
    m_Shinines(1),
    m_ShininesStrength(10)
{
}

se::Material::~Material()
{
}

void se::Material::SetName(const std::string& name)
{
    m_Name = name;
}

void se::Material::SetAmbientColor(const float& r, const float& g, const float& b)
{
    m_AmbientColor = glm::vec3(r, g, b);
}

void se::Material::SetAmbientColor(const glm::vec3& color)
{
    m_AmbientColor = color;
}

void se::Material::SetDiffuseColor(const float& r, const float& g, const float& b)
{
    m_DiffuseColor = glm::vec3(r, g, b);
}

void se::Material::SetDiffuseColor(const glm::vec3& color)
{
    m_DiffuseColor = color;
}

void se::Material::SetSpecularColor(const float& r, const float& g, const float& b)
{
    m_SpecularColor = glm::vec3(r, g, b);
}

void se::Material::SetSpecularColor(const glm::vec3& color)
{
    m_SpecularColor = color;
}

void se::Material::SetTransparentMask(const float& r, const float& g, const float& b)
{
    m_TransparentMask = glm::vec3(r, g, b);
}

void se::Material::SetTransparentMask(const glm::vec3& color)
{
    m_TransparentMask = color;
}

void se::Material::SetShinines(const float& value)
{
    m_Shinines = value;
}

void se::Material::SetShininesStrength(const float& value)
{
    m_ShininesStrength = value;
}

const std::string& se::Material::GetName() const
{
    return m_Name;
}

const glm::vec3& se::Material::GetAmbientColor() const
{
    return m_AmbientColor;
}

const glm::vec3& se::Material::GetDiffuseColor() const
{
    return m_DiffuseColor;
}

const glm::vec3& se::Material::GetSpecularColor() const
{
    return m_SpecularColor;
}

const glm::vec3& se::Material::GetTransparentMask() const
{
    return m_TransparentMask;
}

const float& se::Material::GetShinines() const
{
    return m_Shinines;
}

const float& se::Material::GetShininesStrength() const
{
    return m_ShininesStrength;
}

void se::Material::Process(const se::Shader* shader) const
{
    shader->SendUniform3Float("material.colorAmbient",     m_AmbientColor);
    shader->SendUniform3Float("material.colorDiffuse",     m_DiffuseColor);
    shader->SendUniform3Float("material.colorSpecular",    m_SpecularColor);
    shader->SendUniform3Float("material.transparentMask",  m_TransparentMask);
    shader->SendUniform1Float("material.shinines",         m_Shinines);
    shader->SendUniform1Float("material.shininesStrength", m_ShininesStrength);
}
