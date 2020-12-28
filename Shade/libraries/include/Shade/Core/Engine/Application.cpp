#include "stdafx.h"
#include "Application.h"
//#include "Shade/Core/Engine/Scene.h"

se::Application* se::Application::m_pInstance = nullptr;

se::Application::Application()
	:m_ActiveScene(nullptr)
{
	m_pInstance = this;
	SE_DEBUG_PRINT("Application has been created.", se::SLCode::InfoSecondary);

	se::AssetManager::ReadRoadMap(); //Temporary here

	/*SDL_Init(SDL_INIT_AUDIO);
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	SDL_LoadWAV("Test.wav", &wavSpec, &wavBuffer, &wavLength);
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
	SDL_Delay(300000);
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
	SDL_Quit();*/
}

se::Application::~Application()
{
	m_Scenes.clear();
	SE_DEBUG_PRINT("Application has been destroyed.", se::SLCode::InfoSecondary);
}

void se::Application::Start()
{
	

	while (true)
	{
		try
		{
			se::EventManager::Get().Update();
			OnUpdate();
			if (m_ActiveScene)
			{
				m_ActiveScene->OnUpdate();

				se::WindowManager::Get().Clear();
				m_ActiveScene->OnRender();
			}
			else 
			{
				throw se::ShadeException("Active scene isn't set!", se::SECode::Error);
			}
			
			se::WindowManager::Get().Update();
		
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
}

std::map<std::string, se::Scene*>& se::Application::GetScenes()
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
			se::Log::Print(_Msg.c_str(), se::SLCode::Warning);
		}
		
	}
	else
	{
		std::string _Msg("Scene '" + name + "' has not been found!");
		throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
	}
}

void se::Application::SetActiveScene(const std::string& name)
{
	auto _Scene = m_Scenes.find(name);
	if (_Scene != m_Scenes.end())
		m_ActiveScene = _Scene->second;
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
		if (m_ActiveScene == _Scene->second)
			m_ActiveScene = nullptr;

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
