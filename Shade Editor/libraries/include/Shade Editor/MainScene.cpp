#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene(const std::string& name):se::Scene(name)
{
}

MainScene::~MainScene()
{
}

void MainScene::OnCreate()
{
	
}

void MainScene::OnInit()
{
	se::EventManager::RegSceneEventCallback(se::EventType::SDL_KEYDOWN, this, 
		[](se::Event const& event) {

			if (event.key.keysym.sym == se::KeyCode::SDLK_SPACE)
				SE_DEBUG_PRINT("SDLK_SPACE", se::SLCode::Event);

			return false;
		});

	CreateLayer<MainLayer>("MainLayer");

	InitLayers();
}

void MainScene::OnUpdate()
{
	for (auto& layer : GetLayers())
	{
		layer->OnUpdate();
	}
}

void MainScene::OnRender()
{
	for (auto& layer : GetLayers())
	{
		layer->OnRender();
	}
}

void MainScene::OnDelete()
{
}
