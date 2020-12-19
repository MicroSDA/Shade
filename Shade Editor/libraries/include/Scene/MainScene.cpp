#include "MainScene.h"

void MainScene::OnCreate()
{
	//pCamera = new se::Camera(glm::vec3(0.0, 0.0, 0.0), 70.0f, float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), 0.01f, -3000.0f);
}

void MainScene::OnInit()
{
	
	DEBUG_PRINT("On scene Init", se::LogLevel::WARNING);

	AddLayer(new MainLayer("MainLayer", this));
	AddLayer(new MainLayer("SecondLayer", this));

	RegisterEventCallback(se::EventType::SDL_KEYDOWN,
		[](se::Event const& event) {
			if (event.key.keysym.sym == se::KeyCode::SDLK_SPACE)
			{

				DEBUG_PRINT("SceneEvent SPACE", se::LogLevel::EVENT);
			}

			return false;
		});
}

se::SceneState MainScene::OnUpdate()
{
	
	for (const auto& layer : m_Layers)
	{
		layer->OnUpdate();
	}

	return se::SceneState::CONTINUE;
}

void MainScene::OnRender()
{
	se::Render::SetClearColor({ 0.5444f, 0.62f, 0.69f, 1.0f });
	//se::Render::Clear();

	for (const auto& layer : m_Layers)
	{
		layer->OnRender();
	}
	
}

void MainScene::OnDelete()
{
	DEBUG_PRINT("On Scene Delete", se::LogLevel::WARNING);
}
