#include "stdafx.h"
#include "EventManager.h"
#include "Shade/Core/Engine/Application.h"
#include "Shade/Core/Engine/WindowManager.h"
#include "Shade/Core/Engine/Layer.h"

se::EventManager::EventManager():
    m_Event(se::Event())
{
}

se::EventManager::~EventManager()
{
	EraseCallbacks();
}

int se::EventManager::RegAppEventCallback(const EventType& type, const EventCallback& callback)
{
    auto& _Manager = Get();
    //Tyring to safe some pice of performace ?
    _Manager.m_CoreCallbacks[type].emplace_back(callback);
    SE_DEBUG_PRINT((std::string("Register new application event callback code : ") + std::to_string(type)).c_str(), se::SLCode::InfoSecondary);
    //Return callback index
    return (int)_Manager.m_CoreCallbacks[type].size() - 1;
}

int se::EventManager::RegSceneEventCallback(const EventType& type, const Scene* scene, const EventCallback& callback)
{
    auto& _Manager = Get();
    //Tyring to safe some pice of performace ?
    _Manager.m_SceneCallbacks[type][scene].emplace_back(callback);
    SE_DEBUG_PRINT((std::string("Register new scene event callback code : ") + std::to_string(type)).c_str(), se::SLCode::InfoSecondary);
    //Return callback index
    return (int)_Manager.m_SceneCallbacks[type][scene].size() - 1;
}

int se::EventManager::RegLayerEventCallback(const EventType& type, const Scene* scene, const Layer* layer, const EventCallback& callback)
{
    auto& _Manager = Get();
    //Tyring to safe some pice of performace ?
    _Manager.m_LayerCallbacks[type][scene][layer].emplace_back(callback);
    SE_DEBUG_PRINT((std::string("Register new layer event callback code : ") + std::to_string(type)).c_str(), se::SLCode::InfoSecondary);
    //Return callback index
    return (int)_Manager.m_LayerCallbacks[type][scene][layer].size() - 1;
}

void se::EventManager::PusEvent(Event& event)
{
	SDL_PushEvent(&event);
}

void se::EventManager::DeleteEventCallback(const EventType& type, int index)
{
}

void se::EventManager::DeleteEventCallback(const EventType& type)
{
}

se::EventManager& se::EventManager::Get()
{
    static EventManager _Instatnce;
    return _Instatnce;
}

void se::EventManager::Update()
{
	//Potential momory leak by vector capasity 
	while (SDL_PollEvent(&m_Event) && !se::WindowManager::IsClosed())
	{
		auto* _CurrentScene = se::Application::GetApplication().GetCurrentScene();
		//Core
		for (auto i = 0; i < m_CoreCallbacks[static_cast<EventType>(m_Event.type)].size(); i++)
		{
			if (m_CoreCallbacks[static_cast<EventType>(m_Event.type)][i](m_Event))
			{
				m_CoreCallbacks[static_cast<EventType>(m_Event.type)].erase(
					m_CoreCallbacks[static_cast<EventType>(m_Event.type)].begin() + i);// TODO Issue here, wrong removing, should be removed by while and iterator

				SE_DEBUG_PRINT((std::string("Event callback type: ") + std::to_string(m_Event.type) + " done.").c_str(), se::SLCode::InfoSecondary);
			}
		}
		//Scene
		for (auto i = 0; i < m_SceneCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene].size(); i++)
		{
			// Process scene's events
			if (m_SceneCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene][i](m_Event))
			{   // If event was complited, returned true - remove event from queue
				m_SceneCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene].erase(
					m_SceneCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene].begin() + i); // TODO Issue here, wrong removing, should be removed by while and iterator

				SE_DEBUG_PRINT((std::string("Event callback type: ") + std::to_string(m_Event.type) + " done.").c_str(), se::SLCode::InfoSecondary);
			}
		}

		for (auto& _Layer : m_LayerCallbacks[static_cast<EventType>(m_Event.type)][_CurrentScene])
		{
			if (_Layer.first->IsActive() && _Layer.first->IsEventsUpdate())
			{
				for (auto j = 0; j < _Layer.second.size(); j++)
				{
					if (_Layer.second[j](m_Event))
					{
						_Layer.second.erase(_Layer.second.begin() + j); // TODO Issue here, wrong removing, should be removed by while and iterator
						SE_DEBUG_PRINT((std::string("Event callback type: ") + std::to_string(m_Event.type) + " done.").c_str(), se::SLCode::InfoSecondary);
					}
				}
			}
		}
	}
}

void se::EventManager::EraseCallbacks()
{
    m_CoreCallbacks.clear();
    m_SceneCallbacks.clear();
    m_LayerCallbacks.clear();

    SE_DEBUG_PRINT("All events callbacks have been deleted", se::SLCode::InfoSecondary);
}