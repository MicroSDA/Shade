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
	se::Renderer::SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);
}

void MainScene::OnInit()
{
	{// Assets
		se::Camera*  _MainCamera = new se::Camera();
		se::Model3D* _Model3D	 = se::AssetManager::Hold<se::Model3D>("Assets.Models.Cube");
		se::Shader*  _Shader	 = se::AssetManager::Hold<se::Shader>("Assets.Shaders.BasicModel");
	
		//se::Texture* _Texture = se::AssetManager::Hold<se::Texture>("Assets.Models.Cube.Image");
		SetMainCamera(_MainCamera);

		se::Entity _CubeEntity = CreateEntity();
		_CubeEntity.AddComponent<se::TransformComponent>().Transform.SetPostition(glm::vec3(0,0, 5));
		_CubeEntity.AddComponent<se::ShaderComponent>(_Shader);
		_CubeEntity.AddComponent<se::CameraComponent>(_MainCamera);
		_CubeEntity.AddComponent<se::Model3DComponent>(_Model3D);
		//_CubeEntity.AddComponent<se::TextureComponent>(_Texture);

		se::RenderComponent  _RenderComponent([](se::Entity entity) {
			auto& transform = entity.GetComponent<se::TransformComponent>().Transform;
			auto* shader = entity.GetComponent<se::ShaderComponent>().Shader;
			auto* camera = entity.GetComponent<se::CameraComponent>().Camera;

			shader->Bind();
			shader->SendUniformMatrix4Float("ModelM", GL_FALSE, transform.GetModel());
			shader->SendUniformMatrix4Float("ViewM", GL_FALSE, camera->GetView());
			shader->SendUniformMatrix4Float("ProjectionM", GL_FALSE, camera->GetProjection());
			shader->SendUniform3Float("CameraPosition", camera->GetPosition());
			});
		_CubeEntity.AddComponent<se::RenderComponent>(_RenderComponent);
	}
	{// Controllers
		se::Entity _CameraController = CreateEntity();
		_CameraController.AddComponent<se::CameraComponent>(GetMainCamera());
		_CameraController.AddComponent<se::NativeScriptComponent>().Bind<se::FreeCameraController>();

		se::Entity _GeneralLighController = CreateEntity();
		_GeneralLighController.AddComponent<se::EnvironmentComponent>(new se::PointLight());
		_GeneralLighController.AddComponent<se::NativeScriptComponent>().Bind<se::LightController>();
	}

	CreateLayer<MainLayer>("MainLayer");
	InitLayers();
	//InitLayer TODO !
}
	
void MainScene::OnUpdate(const se::Timer& deltaTime)
{
	{
		UpdateNativeScripts(deltaTime);
	}

	for (auto& layer : GetLayers())
	{
		layer->OnUpdate(deltaTime);
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
	// Delete Camera and light jsut for now here
	{
		auto _Lights = GetRegistry().view<se::EnvironmentComponent>();
		delete _Lights.get<se::EnvironmentComponent>(_Lights[0]).Instance;
	}
	{
		auto _Camera = GetRegistry().view<se::CameraComponent>();
		delete _Camera.get<se::CameraComponent>(_Camera[0]).Camera;
	}
}
