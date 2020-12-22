#include "stdafx.h"
#include "Scene.h"
#include "Shade/Core/Engine/Entity.h"
#include "Shade/Core/Engine/Layer.h"

se::Scene::Scene(const std::string& name) : 
	m_IsInitalized(false)
{
	m_Name = name;
}

se::Scene::~Scene()
{
}

se::Entity se::Scene::CreateEntity()
{
	return { m_Registry.create(), this };
}

entt::registry& se::Scene::GetRegistry()
{
	return m_Registry;
}

void se::Scene::DeleteLayers()
{
	for (auto& layer : m_Layers)
	{
		layer->OnDelete();
		delete layer;
	}
	m_Layers.clear();
}

void se::Scene::InitLayers()
{
	for (auto& layer : m_Layers)
	{
		layer->OnInit();
	}
}
