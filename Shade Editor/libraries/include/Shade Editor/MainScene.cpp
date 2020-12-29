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

	SetMainCamera(camera);

	se::ShaderComponent  shaderComp(shader);
	se::CameraComponent  cameraComp(camera);


	se::RenderComponent  renderComp([](se::Entity entity) {

		
		entity.GetComponent<se::TextureComponent>().Texture->Bind(0);
		auto& transform = entity.GetComponent<se::TransformComponent>().Transform;
		transform.SetRotation(glm::vec3(transform.GetRotation().x + 0.01f, transform.GetRotation().y + 0.01f, 0));
		auto* shader = entity.GetComponent<se::ShaderComponent>().Shader;
		auto* camera = entity.GetComponent<se::CameraComponent>().Camera;

		//camera->MoveBack(0.0001f);

		shader->Bind();
		shader->SendUniformMatrix4fv(0, GL_FALSE, &transform.GetModel()[0][0]);
		shader->SendUniformMatrix4fv(1, GL_FALSE, &camera->GetView()[0][0]);
		shader->SendUniformMatrix4fv(2, GL_FALSE, &camera->GetProjection()[0][0]);

	});

	for (int i = 0 ; i < 10; i++)
	{
		se::Entity entity = CreateEntity();
		entity.AddComponent<se::TransformComponent>().Transform.SetPostition(glm::vec3( - i*3, 0, 10));
		entity.AddComponent<se::ShaderComponent>(shaderComp);
		entity.AddComponent<se::CameraComponent>(cameraComp);
		entity.AddComponent<se::Model3DComponent>(se::AssetManager::Hold<se::Model3D>("Assets.Models.Cube"));
		entity.AddComponent<se::TextureComponent>(se::AssetManager::Hold<se::Texture>("Assets.Models.Cube.Image"));
		entity.AddComponent<se::RenderComponent>(renderComp);
	}

	CreateLayer<MainLayer>("MainLayer");
	//InitLayer TODO !
	InitLayers();
	se::Renderer::SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);
}

void MainScene::OnUpdate()
{
	//GetMainCamera()->Resize();

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
