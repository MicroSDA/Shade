#include "EventManager.h"
#include <core/engine/WindowManager.h>

se::EventManager::EventManager()
	:m_Event(Event())
{
}

se::EventManager::~EventManager()
{
	if (m_CoreCallbacks.size())
	{
		EraseCallbacks();
	}
	
}

se::EventManager& se::EventManager::GetInstance()
{
	static EventManager _Instatnce;
	return _Instatnce;
}

void se::EventManager::Update()
{
	//Potential momory leak by vector capasity 
	while (SDL_PollEvent(&m_Event))
	{
		if (m_Event.type == se::EventType::SDL_QUIT)
			WindowManager::Close();

		const Scene* _CurrentScene = Engine::GetCurrentScene();
		//Core
		for (auto i = 0; i < m_CoreCallbacks[static_cast<EventType>(m_Event.type)].size(); i++)
		{
			if (m_CoreCallbacks[static_cast<EventType>(m_Event.type)][i](m_Event))
			{
				m_CoreCallbacks[static_cast<EventType>(m_Event.type)].erase(
					m_CoreCallbacks[static_cast<EventType>(m_Event.type)].begin() + i);
			
				DEBUG_PRINT("Event Callback type: " + std::to_string(m_Event.type) +" done.", LogLevel::INFO_SECONDARY);
			}
		}
		//Scene
		for (auto i = 0; i < m_SceneCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene].size(); i++)
		{
			if (m_SceneCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene][i](m_Event))
			{
				m_SceneCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene].erase(
					m_SceneCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene].begin() + i);

				DEBUG_PRINT("Event Callback type: " + std::to_string(m_Event.type) + " done.", LogLevel::INFO_SECONDARY);
			}
		}
		//Layer
		for (auto& scene : m_LayerCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene])
		{
			for (int i = 0; i < scene.second.size(); i++)
			{
				if (scene.second[i](m_Event))
				{
					scene.second.erase(scene.second.begin() + i);
					DEBUG_PRINT("Event Callback type: " + std::to_string(m_Event.type) + " done.", LogLevel::INFO_SECONDARY);
				}
			}
			
		}
	}
}

int se::EventManager::RegisterEventCoreCallback(const EventType& type, const EventCallback& callback)
{
	return GetInstance()._RegisterEventCoreCallback(type, callback);
}

int se::EventManager::RegisterSceneCallback(const EventType& type, const Scene* scene, const EventCallback& callback)
{
	return GetInstance()._RegisterSceneCallback(type, scene, callback);
}

int se::EventManager::RegisterLayerCallback(const EventType& type, const Scene* scene, const Layer* layer, const EventCallback& callback)
{
	return GetInstance()._RegisterLayerCallback(type, scene, layer, callback);
}



int se::EventManager::_RegisterEventCoreCallback(const EventType& type, const EventCallback& callback)
{
	DEBUG_PRINT("Register new Event Core Callback type: " + std::to_string(type), LogLevel::INFO_SECONDARY);
	//Tyring to safe some pice of performace ?
	m_CoreCallbacks[type].emplace_back(callback);
	//Return callback index
	return m_CoreCallbacks[type].size() - 1;
}
int se::EventManager::_RegisterSceneCallback(const EventType& type, const Scene* scene, const EventCallback& callback)
{
	DEBUG_PRINT("Register new Event Scene Callback type: " + std::to_string(type), LogLevel::INFO_SECONDARY);
	//Tyring to safe some pice of performace ?
	m_SceneCallbacks[type][scene].emplace_back(callback);
	//Return callback index
	return m_SceneCallbacks[type][scene].size() - 1;
}

int se::EventManager::_RegisterLayerCallback(const EventType& type, const Scene* scene, const Layer* layer, const EventCallback& callback)
{
	DEBUG_PRINT("Register new Event Scene Callback type: " + std::to_string(type), LogLevel::INFO_SECONDARY);
	//Tyring to safe some pice of performace ?
	m_LayerCallbacks[type][scene][layer].emplace_back(callback);
	//Return callback index
	return m_LayerCallbacks[type][scene][layer].size() - 1;
}

void se::EventManager::EraseCallbacks()
{
	m_CoreCallbacks.clear();
	m_SceneCallbacks.clear();
	m_LayerCallbacks.clear();

	DEBUG_PRINT("All events callbacks have been deleted", LogLevel::INFO_SECONDARY);
}
