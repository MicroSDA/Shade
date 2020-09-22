#include "Layer.h"
#include <core/engine/EventManager.h>


se::Layer::Layer(const std::string& name, const void* scene)
	:m_Name(name), m_Scene(scene)
{
}

se::Layer::~Layer()
{
}

void se::Layer::RegisterEventCallback(const EventType& type, const EventCallback& callback)
{
	se::EventManager::RegisterLayerCallback(type, static_cast<const Scene*>(m_Scene), this, callback);
}
