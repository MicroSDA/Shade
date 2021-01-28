#include "stdafx.h"
#include "Scene.h"
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

	this->GetEntities().view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			if (nsc.Instance)
			{
				nsc.Instance->OnDestroy();
				nsc.DestroyScript(&nsc);
			}
		});

	this->GetEntities().clear();
	SE_DEBUG_PRINT(std::string("Scene '" + m_Name + "' has been destroyed").c_str(), se::SLCode::InfoSecondary);
}

void se::Scene::UpdateNativeScripts(const se::Timer& deltaTime)
{
	this->GetEntities().view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
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
		if (!layer->m_IsInitalized)
		{
			layer->OnInit();
			layer->m_IsInitalized = true;
		}
		else
		{
			std::string _Msg("Layer '" + layer->GetName() + "' is already initialized!");
			SE_DEBUG_PRINT(_Msg.c_str(), se::SLCode::Warning);
		}

	}
}

void se::Scene::InitLayer(const std::string& name)
{
	for (auto& layer : m_Layers)
	{
		if (layer->GetName() == name)
		{
			if (!layer->m_IsInitalized)
			{
				layer->OnInit();
				layer->m_IsInitalized = true;
				return;
			}
			else
			{
				std::string _Msg("Layer '" + layer->GetName() + "' is already initialized!");
				SE_DEBUG_PRINT(_Msg.c_str(), se::SLCode::Warning);
				return;
			}
		}
	}

	throw se::ShadeException(std::string("Layer intializing failed, layer '" + name + "' isn't found !").c_str(), se::SECode::Warning);
}

se::Camera* se::Scene::GetMainCamera()
{
	return m_pMainCamera;
}

void se::Scene::SetMainCamera(se::Camera* camera)
{
	m_pMainCamera = camera;
}

inline se::Layer* se::Scene::GetLayer(const std::string& name)
{
	
	for (auto& _Layer : m_Layers)
	{
		if (_Layer->GetName() == name)
			return _Layer;
	}

	throw se::ShadeException(std::string("Layer '" + name + "' doesn't exist in '" + m_Name + "' scene!").c_str(), se::SECode::Error);
}

se::ShadeShared<se::FrameBuffer> se::Scene::GetFrameBuffer(const std::string& name)
{
	if (m_FrameBuffers.find(name) != m_FrameBuffers.end())
	{
		return m_FrameBuffers[name];
	}
	else
	{
		SE_DEBUG_PRINT(std::string("Frame buffer '"+ name +"' doesn't exist!").c_str(), se::SLCode::Warning);
		return se::ShadeShared<se::FrameBuffer>(nullptr); // nullptr or need to thorw 
	}
}

void se::Scene::CreateFrameBuffer(const std::string& name, const se::FramebufferSpec& spec)
{
	if (m_FrameBuffers.find(name) == m_FrameBuffers.end())
	{
		m_FrameBuffers.emplace(name, se::FrameBuffer::Create(spec));
	}
}


