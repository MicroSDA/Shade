#include "Engine.h"
#include <core/engine/WindowManager.h>
#include <core/engine/EventManager.h>

se::Engine::Engine()
	: m_State(EngineState::RUNNING), m_CurrentScene(nullptr)
{
}
se::Engine::~Engine()
{	
	DEBUG_PRINT("Engine has been destroyed", LogLevel::INFO_SECONDARY);
}

se::Engine& se::Engine::GetInstance()
{
	static Engine _Instatnce;
	return _Instatnce;
}

void se::Engine::SetConfig(const EngineConfig& config)
{
	GetInstance()._SetConfig(config);
}

void se::Engine::SetState(const EngineState& state)
{
	GetInstance()._SetState(state);
}

void se::Engine::Init()
{
	try 
	{
		GetInstance()._Init();
	}
	catch (std::runtime_error& error)
	{
#ifdef SE_DEBUG
		DEBUG_PRINT(error.what(), LogLevel::ERROR);
#else 
		DEBUG_SAVE(error.what(),  LogLevel::ERROR);
#endif // SE_DEBUG
		exit(-1);
	}
}

void se::Engine::RegisterEventCallback(const EventType& type, const se::EventCallback& callback)
{
	GetInstance()._RegisterEventCallback(type, callback);
}

void se::Engine::_SetConfig(const EngineConfig& config)
{
	m_Config = config;
}

void se::Engine::_SetState(const EngineState& state)
{
	m_State = state;
}

void se::Engine::_Init()
{
	m_CurrentScene = m_Config.scene;
	WindowManager::CreateWindow(m_Config.window);

	Prepare();
	Start();
}

void se::Engine::_RegisterEventCallback(const EventType& type, const se::EventCallback& callback)
{
	EventManager::RegisterEventCoreCallback(type, callback);
}

void se::Engine::Start()
{
	
	while (true) //TODO some like vent for exit or other things
	{
		EventManager::GetInstance().Update();

		if (!WindowManager::IsClosed())
			m_State == EngineState::STOP;

		switch (m_State)
		{
		case EngineState::RUNNING:
			Update();
			break;
		case EngineState::PAUSE:

			break;
		case EngineState::STOP:
			Stop();
			return;
		default:
			break;
		}

		WindowManager::GetInstance().Update();
	}

}

void se::Engine::Prepare()
{
	
	m_CurrentScene->OnCreate();
	m_CurrentScene->OnInit();

}

void se::Engine::Update()
{
	
	
	if (m_CurrentScene != nullptr)
	{
		//Should be binded to scene ! update events and etc
	
		switch (m_CurrentScene->OnUpdate())
		{
		case SceneState::CONTINUE:
			m_CurrentScene->OnRender();
			break;
		case SceneState::STOP:
			m_State = EngineState::STOP;
			break;
		case SceneState::NEXTSCENE:
			//TODO: 
			break;
		case SceneState::PREVIOUSSCENE:
			//TODO: 
			break;
		default:
			break;
		}
		
		//TODO: Update physics
		//TODO:	Network Update if needed	
	}

}

void se::Engine::Termintae()
{
	EventManager::GetInstance().EraseCallbacks();
}

void se::Engine::Stop()
{
	//TODO: idk, stop some thread or process ect..

	se::WindowManager::GetInstance().Close();

	m_CurrentScene->OnDelete();
	delete m_CurrentScene;
	
	Termintae();
}

