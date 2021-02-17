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

void se::Layer::SetActive(const bool& isActive)
{
	m_IsActive = isActive;
}

void se::Layer::SetEventsUpdate(const bool& isEventUpdate)
{
	m_IsEventsUpdate = isEventUpdate;
}

void se::Layer::SetRender(const bool& isRender)
{
	m_IsRender = isRender;
}

void se::Layer::SetUpdate(const bool& isUpdate)
{
	m_IsUpdate = isUpdate;
}

void se::Layer::SetOnEvent(const bool& isEvent)
{
	m_IsOnEvent = isEvent;
}

const bool& se::Layer::IsActive() const
{
	return m_IsActive;
}

const bool& se::Layer::IsOnEvent() const
{
	return m_IsOnEvent;
}

const bool& se::Layer::IsRender() const
{
	return m_IsRender;
}

const bool& se::Layer::IsUpdate() const
{
	return m_IsUpdate;
}
