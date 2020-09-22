#include "MainScene.h"

void MainScene::OnCreate()
{
}

void MainScene::OnInit()
{

	DEBUG_PRINT("On scene Init", se::LogLevel::WARNING);

	AddLayer(new MainLayer("MainLayer", this));

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
	for (const auto& layer : m_Layers)
	{
		layer->OnRender();
	}
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.5444f, 0.62f, 0.69f, 1.0f);
}

void MainScene::OnDelete()
{
	DEBUG_PRINT("OnLayer Delete", se::LogLevel::INFO_PRIMARY);
}
