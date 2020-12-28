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


	se::Shader* shader = se::AssetManager::Hold<se::Shader>("Assets.Shaders.BasicModel");
	se::Camera* camera = new se::Camera();

	se::ShaderComponent  shaderComp(shader);
	se::CameraComponent  cameraComp(camera);

	se::RenderComponent  renderComp([](se::Entity entity) {

		auto& transform = entity.GetComponent<se::TransformComponent>().Transform;
		transform.SetRotation(glm::vec3(transform.GetRotation().x + 0.01f, 0, 0));
		auto* shader = entity.GetComponent<se::ShaderComponent>().Shader;
		auto* camera = entity.GetComponent<se::CameraComponent>().Camera;

		shader->Bind();
		shader->SendUniformMatrix4fv(0, GL_FALSE, &transform.GetModel()[0][0]);
		shader->SendUniformMatrix4fv(1, GL_FALSE, &camera->GetView()[0][0]);
		shader->SendUniformMatrix4fv(2, GL_FALSE, &camera->GetPerpective()[0][0]);

	});

	for (int i = 0 ; i < 3; i++)
	{
		se::Entity entity = CreateEntity();
		entity.AddComponent<se::TransformComponent>().Transform.SetPostition(glm::vec3(-i*3, 0, 10));
		entity.AddComponent<se::ShaderComponent>(shaderComp);
		entity.AddComponent<se::CameraComponent>(cameraComp);
		entity.AddComponent<se::Model3DComponent>(se::AssetManager::Hold<se::Model3D>("Assets.Models.Cube"));
		entity.AddComponent<se::RenderComponent>(renderComp);
	}


	CreateLayer<MainLayer>("MainLayer");
	//InitLayer TODO !
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
