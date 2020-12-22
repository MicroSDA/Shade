#include "stdafx.h"
#include "ShadeEditor.h"
#include "Serializer.h"

ShadeEditor::ShadeEditor()
{
	Serializer ser;
	ser.SerializeModel("cube.obj");
}

ShadeEditor::~ShadeEditor()
{
}

void ShadeEditor::OnInit()
{
	//Events call back an other stuff 

	se::WindowManager::Create(se::Window{});
	se::EventManager::RegAppEventCallback(se::EventType::SDL_WINDOWEVENT,
		[](se::Event const& event) {

			if (event.window.event == SDL_WINDOWEVENT_MINIMIZED)
			{
				SE_DEBUG_PRINT("WINDOWEVENT_MINIMIZED", se::SLCode::Event);
			}

			if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
			{
				SE_DEBUG_PRINT("WINDOWEVENT_FOCUS_GAINED", se::SLCode::Event);
			}

			return false;
		});
	se::EventManager::RegAppEventCallback(se::EventType::SDL_QUIT,
		[](se::Event const& event) {

			se::WindowManager::DestroyWindow();
			exit(0);
			return true;
		});

	CreateScene<MainScene>("MainScene");

	//? or more
	
	for (auto const& [name, scene] : GetScenes())
	{
		InitScene(name);
	}

	SetActiveScene("MainScene");
	//DeleteScene("MainScene");
}

void ShadeEditor::OnUpdate()
{
	return;
}

se::Application* se::CreateApplication()
{
	return new ShadeEditor();
}

