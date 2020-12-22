#include "stdafx.h"
#include "Layer.h"

se::Layer::Layer(const std::string& name, se::Scene* scene):
	m_Name(name), m_pScene(scene)
{
	
}

se::Layer::~Layer()
{
}
