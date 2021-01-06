#include "stdafx.h"
#include "Layer.h"

se::Layer::Layer(const std::string& name, se::Scene* scene):
	m_IsInitalized(false), m_Name(name), m_pScene(scene), m_IsActive(true)
{
	
}

se::Layer::~Layer()
{
	SE_DEBUG_PRINT(std::string("Layer '" + m_Name + "' has been destroyed").c_str(), se::SLCode::InfoSecondary);
}

void se::Layer::SetActive(const bool& isActive)
{
	m_IsActive = isActive;
}

const bool& se::Layer::IsActive() const
{
	return m_IsActive;
}
