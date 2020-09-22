#include "Scene.h"
#include <core/engine/Engine.h>
#include <core/engine/EventManager.h>

se::Scene::Scene(const std::string& name):
	m_Name(name)
{
}

se::Scene::~Scene()
{
	for (auto& layer : m_Layers)
	{
		layer->OnDelete();
		delete layer;
	}
}

void se::Scene::SetScene(const std::string& name)
{
	try
	{
		if (Engine::GetInstance().m_Scenes.find(name) != Engine::GetInstance().m_Scenes.end())
		{
			Engine::GetInstance().m_CurrentScene = Engine::GetInstance().m_Scenes.find(name)->second;
		}
		else
		{
			throw std::runtime_error("Exeption : Scene wasn't founded: "+ name);
		}
	}
	catch (std::runtime_error& error)
	{
		DEBUG_PRINT(error.what(), LogLevel::ERROR);
	}
	
}

void se::Scene::RegisterEventCallback(const EventType& type, const EventCallback& callback)
{
	se::EventManager::RegisterSceneCallback(type, this, callback);
}

void se::Scene::AddLayer(Layer* layer)
{
	m_Layers.emplace_back(layer);

	layer->OnCreate();
	layer->OnInit();
}
