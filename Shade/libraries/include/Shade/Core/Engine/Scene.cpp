#include "stdafx.h"
#include "Scene.h"
#include "Shade/Core/Engine/Entity.h"
#include "Shade/Core/Engine/Layer.h"

se::Scene::Scene(const std::string& name) : 
	m_IsInitalized(false), m_pMainCamera(nullptr)
{
	m_Name = name;
}

se::Scene::~Scene()
{
	for (auto& layer : m_Layers)
	{
		layer->OnDelete();
		delete layer;
	}
	m_Layers.clear();

	m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			if (nsc.Instance)
			{
				nsc.Instance->OnDestroy();
				nsc.DestroyScript(&nsc);
			}
		});

	SE_DEBUG_PRINT(std::string("Scene '"+ m_Name +"' has been destroyed").c_str(), se::SLCode::InfoSecondary);
}

se::Entity se::Scene::CreateEntity()
{
	return { m_Registry.create(), this };
}

entt::registry& se::Scene::GetRegistry()
{
	return m_Registry;
}

void se::Scene::UpdateNativeScripts(const se::Timer& deltaTime)
{
	m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			// TODO: Move to Scene::OnScenePlay
			if (!nsc.Instance)
			{
				nsc.Instance = nsc.InstantiateScript();
				nsc.Instance->m_Entity = Entity{ entity, this };
				nsc.Instance->OnCreate();
			}

			nsc.Instance->OnUpdate(deltaTime);
		});
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

se::Camera* se::Scene::GetMainCamera()
{
	return m_pMainCamera;
}

void se::Scene::SetMainCamera(se::Camera* camera)
{
	m_pMainCamera = camera;
}

