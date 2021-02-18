#include "stdafx.h"
#include "EventManager.h"
#include "Shade/Core/Engine/Application.h"
#include "Shade/Core/Engine/WindowManager.h"
#include "Shade/Core/Engine/Layer.h"
#include <SDL2/SDL.h>

se::EventManager::EventManager()
{
}

se::EventManager::~EventManager()
{
	
}

se::EventManager& se::EventManager::Get()
{
    static EventManager _Instatnce;
    return _Instatnce;
}

void se::EventManager::Update()
{
	auto&  app = se::Application::GetApplication();
	auto*  scene = app.GetCurrentScene();

	SDL_Event sdl_event;
	while (SDL_PollEvent(&sdl_event))
	{
		se::Event event;
		event = sdl_event;
		event.m_SdlEvent = sdl_event;
		app.OnEvent(event);

		if(scene->IsOnEvent())
			scene->OnEvent(event);

		for (auto& layer : scene->GetLayers())
		{
			if (layer->IsOnEvent())
				layer->OnEvent(event);
		}
	}
}
void se::EventManager::PusEvent(const se::Event& event)
{
	SDL_Event sdl_event;

	/*sdl_event.type					= static_cast<uint32_t>(event.GetType());
	sdl_event.window.event			= static_cast<uint8_t>(event.GetWindow());
	sdl_event.key.keysym.scancode	= static_cast<SDL_Scancode>(event.GetKeyboard().ScanCode);*/
	
	sdl_event.type = static_cast<uint32_t>(event.GetType());
	sdl_event.window.event = static_cast<uint8_t>(event.GetWindow());
	sdl_event.key.keysym.scancode = static_cast<SDL_Scancode>(event.GetKeyboard().ScanCode);

	sdl_event.motion.x = event.GetMouse().Motion.x;
	sdl_event.motion.y = event.GetMouse().Motion.y;
	sdl_event.button.state = static_cast<uint8_t>(event.GetMouse().Button.State);
	sdl_event.button.button = static_cast<uint8_t>(event.GetMouse().Button.Code);
	
	SDL_PushEvent(&sdl_event);
}
