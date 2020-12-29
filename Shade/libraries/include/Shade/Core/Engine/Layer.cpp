#include "stdafx.h"
#include "Layer.h"

se::Layer::Layer(const std::string& name, se::Scene* scene):
	m_Name(name), m_pScene(scene)
{
	
}

se::Layer::~Layer()
{
	SE_DEBUG_PRINT(std::string("Layer '" + m_Name + "' has been destroyed").c_str(), se::SLCode::InfoSecondary);
}
