#include "stdafx.h"
#include "Application.h"
#include "Shade/Core/Engine/Layer.h"

se::Application* se::Application::m_pInstance = nullptr;

se::Application::Application()
	:m_pCurrentScene(nullptr), m_IsQuitRequested(false)
{
	if (m_pInstance)
		throw se::ShadeException("Application already exists!", se::SECode::Error);

	m_pInstance = this;
	SE_DEBUG_PRINT("Application has been created.", se::SLCode::InfoSecondary);

	se::EventManager::RegAppEventCallback(se::EventType::SDL_WINDOWEVENT,
		[](se::Event const& event) {
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				se::WindowManager::Resize();
			}
		
			return false;
		});
}

se::Application::~Application()
{
	for (auto& scene : m_Scenes)
	{
		scene.second->OnDelete();
		delete scene.second;
	}

	m_Scenes.clear();
	SE_DEBUG_PRINT("Application has been destroyed.", se::SLCode::InfoSecondary);
}

se::Application& se::Application::GetApplication()
{
	return *m_pInstance;
}

void se::Application::Start()
{
	se::Timer _DeltaTime;

	while (!m_IsQuitRequested)
	{
		_DeltaTime.Update(); // TODO Check

		try
		{
			se::EventManager::Get().Update();
			OnUpdate(_DeltaTime);
			if (m_pCurrentScene)
			{
				m_pCurrentScene->OnUpdate(_DeltaTime);
				m_pCurrentScene->UpdateNativeScripts(_DeltaTime);
				m_pCurrentScene->OnRender();
				for (auto _Layer : m_pCurrentScene->GetLayers())
				{
					if (_Layer->IsActive())
					{
						if (_Layer->IsUpdate())
							_Layer->OnUpdate(_DeltaTime);
						
						if (_Layer->IsRender())
						{
							_Layer->OnRenderBegin();
							_Layer->OnRender();
							_Layer->OnRenderEnd();
						}
							
					}
				}
			}
			else 
			{
				throw se::ShadeException("Active scene isn't set!", se::SECode::Error);
			}
			
			
			se::WindowManager::Get().Update();
			se::WindowManager::Get().Clear();
			
		}
		catch (se::ShadeException& exception)
		{
			switch (exception.code())
			{
				case SECode::Warning:
				{ //TODO: Change to the debug print
					se::Log::Print((std::string("Exception: ") + exception.what()).c_str(), se::SLCode::Warning);
					break;
				}
				case SECode::Error:
				{
					se::Log::Print((std::string("Exception: ") + exception.what()).c_str(), se::SLCode::Error);
					exit((int)SECode::Error);
					break;
				}
				default:
					break;
			}
		}

	
	}

	se::AssetManager::Clear();
	se::WindowManager::DestroyWindow();
}

void se::Application::Quit()
{
	m_IsQuitRequested = true;
}

std::unordered_map<std::string, se::Scene*>& se::Application::GetScenes()
{
	return m_Scenes;
}

se::Scene* se::Application::GetScene(const std::string& name)
{
	auto _Scene = m_Scenes.find(name);
	if (_Scene != m_Scenes.end())
		return _Scene->second;
	else
	{
		std::string _Msg("Scene '" + name + "' has not been found!");
		throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
	}
		
}

void se::Application::InitScene(const std::string& name)
{
	auto _Scene = m_Scenes.find(name);
	if (_Scene != m_Scenes.end())
	{
		if(!_Scene->second->m_IsInitalized)
		{ 
			_Scene->second->OnInit();
			_Scene->second->m_IsInitalized = true;
			SE_DEBUG_PRINT(std::string("'"+name +"' scene has been initialized").c_str(), se::SLCode::InfoSecondary);
		}
		else
		{
			std::string _Msg("Scene '" + name + "' is already initialized!");
			SE_DEBUG_PRINT(_Msg.c_str(), se::SLCode::Warning);
		}
		
	}
	else
	{
		std::string _Msg("Scene '" + name + "' has not been found!");
		throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
	}
}

void se::Application::SetCurentScene(const std::string& name)
{
	auto _Scene = m_Scenes.find(name);
	if (_Scene != m_Scenes.end())
		m_pCurrentScene = _Scene->second;
	else
	{
		std::string _Msg("Scene '" + name + "' has not been found!");
		throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
	}
}

void se::Application::DeleteScene(const std::string& name)
{
	auto _Scene = m_Scenes.find(name);
	if (_Scene != m_Scenes.end())
	{
		if (m_pCurrentScene == _Scene->second)
			m_pCurrentScene = nullptr;

		_Scene->second->OnDelete();
		delete _Scene->second;
		m_Scenes.erase(_Scene);
		SE_DEBUG_PRINT(std::string("'" + name + "' scene has been deleted").c_str(), se::SLCode::InfoSecondary);
		
	}
	else
	{
		std::string _Msg("Scene '" + name + "' has not been found!");
		throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
	}
}
