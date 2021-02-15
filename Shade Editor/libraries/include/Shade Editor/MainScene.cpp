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

	CreateLayer<MainLayer>("Main");	    InitLayer("Main");
	CreateLayer<TestLayer>("Editor");   InitLayer("Editor");
	

	//se::Renderer::SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);
	se::Renderer::SetClearColor(0.46f, 0.61f, 0.66f, 1.0f);
	//Camera
	se::Entity   mainCamera = this->CreateEntity("Camera");
	mainCamera.AddComponent<se::CameraComponent>(new se::Camera()).IsPrimary = true;
	mainCamera.AddComponent<se::NativeScriptComponent>().Bind<se::FreeCameraController>();
	SetActiveCamera(mainCamera.GetComponent<se::CameraComponent>().Camera);/*
	//Lights

	CreateEntity("General light").AddComponent<se::EnvironmentComponent>(se::ShadeShared<se::Environment>(new se::GeneralLight()));
	CreateEntity("Point light").AddComponent<se::EnvironmentComponent>(se::ShadeShared<se::Environment>(new se::PointLight()));*/
	//CreateEntity("Spot light").AddComponent<se::EnvironmentComponent>(se::ShadeShared<se::Environment>(new se::SpotLight()));
}

void MainScene::OnInit()
{
	/*se::Entity grid = this->CreateEntity("Grid"); // TODO move to Aplication entt
	grid.AddComponent<se::Transform3DComponent>();
	grid.AddComponent<se::DrawableComponent>(se::ShadeShared<se::Drawable>(new se::Grid(500, 500, 500)));


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
}

void MainScene::OnUpdate(const se::Timer& deltaTime)
{
	// TODO Change calculatin model matrix, get new matrix every set pos, scale or rotate; and add z rotation to 2dmatrix

	if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_Q))
	{
		se::Renderer::PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		se::Renderer::PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}


}

void MainScene::OnRender()
{

}

void MainScene::OnDelete()
{

}
