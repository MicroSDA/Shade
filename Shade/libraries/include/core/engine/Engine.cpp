#include "Engine.h"

se::Engine::Engine()
	:m_CurrentScene(nullptr)
{
	DEBUG_LOG("Engine has been created", LOG_LEVEL::INFO_SECONDARY);
}

se::Engine::~Engine()
{
	Clean();
	DEBUG_LOG("Engine has been destroyed", LOG_LEVEL::INFO_SECONDARY);
}

se::Engine& se::Engine::GetInstance()
{
	static Engine _Instatnce;
	return _Instatnce;
}

void se::Engine::Start()
{
	return GetInstance()._Start();
}


void se::Engine::_Start()
{
	Prepare();
	DEBUG_LOG("Engine start", LOG_LEVEL::SUCCESS);
	Run();
}

void se::Engine::Prepare()
{
	DEBUG_LOG("Engine prepare state", LOG_LEVEL::INFO_SECONDARY);

	for (const auto& scene : m_Scenes)
		scene.second->OnCreate();

	//Create default window
	WindowManager::CreateWindow(Window{});

	SDL_Event &event = WindowManager::GetWindow().Event;

	//Registr some events
	auto _Window = [&event]() {
		switch (event.display.event)
		{
		case EventType::WindowClosed:
			DEBUG_LOG("Window Closed", LOG_LEVEL::EVENT);
			WindowManager::Close();
			return false; // Then no need to handle this event anymore and it will be deletet
			break;
		case EventType::WindowResized:
			DEBUG_LOG("Window Resized", LOG_LEVEL::EVENT);
			return true; // keep traking event
			break;
		case EventType::WindowMoved:
			DEBUG_LOG("Window Moved", LOG_LEVEL::EVENT);
			return true;
			break;
		default:
			return true;
			break;
		}
	};
	auto _KeyBoard = [&event]() {
		DEBUG_LOG("KeyBoard", LOG_LEVEL::EVENT);
		return true;
	};

	//Push events to update
	EventManager::OnEvent(EventCategory::WINDOW,   _Window);
	EventManager::OnEvent(EventCategory::KEYBOARD, _KeyBoard);
	
}

void se::Engine::Run()
{
	DEBUG_LOG("Engine run", LOG_LEVEL::SUCCESS);

	while (!WindowManager::IsClosed())
	{

		EventManager::Update();

		if (m_CurrentScene->OnUpdate() == SceneState::Exit)
		{
			break;
		}

		m_CurrentScene->OnRender();

		WindowManager::Update();

	}

	Stop();
}

void se::Engine::Render()
{
	/*glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/

	
}

void se::Engine::Stop()
{
	DEBUG_LOG("Engine stop", LOG_LEVEL::SUCCESS);
	for (const auto& scene : m_Scenes)
	{
		scene.second->OnDelete();
		delete scene.second;
	}
		
	m_Scenes.clear();
	SDL_Quit();
}

void se::Engine::Clean()
{
	DEBUG_LOG("Engine clean", LOG_LEVEL::INFO_SECONDARY);

}
