#include "stdafx.h"
#include "MainScene.h"
//#include "Shade/Core/Engine/ImGuiLayer.h"

MainScene::MainScene(const std::string& name) :se::Scene(name)
{

}

MainScene::~MainScene()
{

}

void MainScene::OnCreate()
{

	CreateLayer<MainLayer>("Main");				InitLayer("Main");
	CreateLayer<EditorLayer>("Editor");			InitLayer("Editor");
	CreateLayer<ModelPreviewLayer>("Model");    InitLayer("Model");
	se::Renderer::SetClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}

void MainScene::OnInit()
{
	/*se::Entity grid = this->CreateEntity("Grid"); // TODO move to Aplication entt
	grid.AddComponent<se::Transform3DComponent>();
	grid.AddComponent<se::DrawableComponent>(se::ShadeShared<se::Drawable>(new se::Grid(500, 500, 500)));/*


	// Assets
	auto floor = se::AssetManager::Hold<se::Model3D>("Models.Floor", false);
	auto cube = se::AssetManager::Hold<se::Model3D>("Models.Cube", false);
	auto skull = se::AssetManager::Hold<se::Model3D>("Models.Skull", false);
	// Entities
	se::Entity floorEntity = CreateEntity("Floor");
	floorEntity.AddComponent<se::Model3DComponent>(floor);
	floorEntity.AddComponent<se::Transform3DComponent>();

	se::Entity cubeEntity = CreateEntity("Cube");
	cubeEntity.AddComponent<se::Model3DComponent>(cube);
	cubeEntity.AddComponent<se::Transform3DComponent>();

	se::Entity skullEntity = CreateEntity("Skull");
	skullEntity.AddComponent<se::Model3DComponent>(skull);
	skullEntity.AddComponent<se::Transform3DComponent>();*/

	/*auto skull = se::AssetManager::Hold<se::Model3D>("Models.Skull", se::Asset::Flag::KeepAlive);

	for (unsigned int i = 0; i < 10; i++)
	{
		float x = 0 + rand() % 50;
		float y = 1 + rand() % 20;
		float z = 0 + rand() % 50;
		se::Entity skullEntity = CreateEntity("Skull");
		skullEntity.AddComponent<se::Model3DComponent>(skull);
		skullEntity.AddComponent<se::Transform3DComponent>().Transform.SetPostition(x, y, z);

		se::PointLight* p = new se::PointLight();
		p->SetPosition(x, y + 1, z);
		p->SetConstant(-1.0);
		CreateEntity("Spot light").AddComponent<se::EnvironmentComponent>(se::ShadeShared<se::Environment>(p));
	}*/
}

void MainScene::OnUpdate(const se::Timer& deltaTime)
{
	auto �ameras = this->GetEntities().view<se::CameraComponent>();
	for (auto& camera : �ameras)
	{
		auto& camera_component = �ameras.get<se::CameraComponent>(camera);
		if (camera_component.IsPrimary)
		{
			this->SetActiveCamera(camera_component.Camera);
			break;
		}
	}

	/*if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_Q))
	{
		se::Renderer::PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		se::Renderer::PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}*/

}

void MainScene::OnRender()
{
}

void MainScene::OnDelete()
{

}

void MainScene::OnEvent(const se::Event& event)
{

}
