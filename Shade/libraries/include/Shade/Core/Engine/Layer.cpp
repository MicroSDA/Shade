#include "Layer.h"
#include <Shade/Core/Engine/EventManager.h>

se::Layer::Layer(const std::string& name, se::Scene* scene)
	:m_Name(name), m_pScene(scene)
{
}

se::Layer::~Layer()
{
}

void se::Layer::RegisterEventCallback(const EventType& type, const EventCallback& callback)
{
	se::EventManager::RegisterLayerCallback(type, static_cast<const Scene*>(m_pScene), this, callback);
}
