#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene(const std::string& name) :se::Scene(name)
{

}

MainScene::~MainScene()
{

}

void MainScene::OnCreate()
{
	
	se::EventManager::RegSceneEventCallback(se::EventType::SDL_KEYDOWN, this, 
		[&](se::Event const& event) {
		
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				se::Entity _CubeEntity = this->CreateEntity();
				_CubeEntity.AddComponent<se::TransformComponent>().Transform.SetPostition(glm::vec3(0 + rand() % 50, 0, 5));
				_CubeEntity.AddComponent<se::Model3DComponent>(se::AssetManager::Hold<se::Model3D>("Assets.Models.Cube"));
			}

			return false;
		});

	//se::Renderer::SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);
}

void MainScene::OnInit()
{
	se::Camera* _MainCamera = new se::Camera();
	_MainCamera->SetPosition(0, 3, -5);
	SetMainCamera(_MainCamera);


	{// Assets
		se::Model3D* _Floor	     = se::AssetManager::Hold<se::Model3D>("Assets.Models.Floor");
		se::Model3D* _Cube	     = se::AssetManager::Hold<se::Model3D>("Assets.Models.Cube");
		se::Model3D* _Samurai	 = se::AssetManager::Hold<se::Model3D>("Assets.Models.SamuraiHelmet");

		se::Entity _FloorEntity = CreateEntity();
		_FloorEntity.AddComponent<se::TransformComponent>();
		_FloorEntity.AddComponent<se::Model3DComponent>(_Floor);

		se::Entity _CubeEntity = CreateEntity();
		_CubeEntity.AddComponent<se::TransformComponent>().Transform.SetPostition(glm::vec3(3, 0.5, 2));
		_CubeEntity.AddComponent<se::Model3DComponent>(_Cube);

		{
			se::Entity _SamuraiEntity = CreateEntity();
			se::Transform _Transform;
			_Transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
			_Transform.SetPostition(glm::vec3(0.0f, 1, 2));
			_SamuraiEntity.AddComponent<se::TransformComponent>(_Transform);
			_SamuraiEntity.AddComponent<se::Model3DComponent>(_Samurai);
		}
		{   // Just for Fun )
			se::Sprite* _POEInterfaceSprite = new se::Sprite();
			_POEInterfaceSprite->Init();
			se::Entity _SpriteEntity = CreateEntity();

			se::Transform2D _Transform;
			_Transform.SetScale(1.0f, 0.20f);
			_Transform.SetPostition(0.0f, - 0.8f);

			_SpriteEntity.AddComponent<se::Transform2DComponent>(_Transform);
			_SpriteEntity.AddComponent<se::TextureComponent>(se::AssetManager::Hold<se::Texture>("Assets.Images.Image"));
			_SpriteEntity.AddComponent<se::SpriteComponent>(_POEInterfaceSprite);
		}
		
		
	}
	{// Light
		se::PointLight* _PointLight = new se::PointLight();
		_PointLight->SetPosition(0.0f, 3.0f, 0.0f);
		_PointLight->SetDiffuseColor(1.0f, 1.0f, 0.917f);
		_PointLight->SetSpecularColor(1.0f, 1.0f, 0.917f);

	
		_PointLight->SetLinear(0.07f);
		_PointLight->SetQaudratic(0.017f);

		se::GeneralLight* _GeneraLight = new se::GeneralLight();
		_GeneraLight->SetDirection(0.0198322f,-0.675238f, 0.737333f);
		
		se::Entity _LightEntity = CreateEntity();
		_LightEntity.AddComponent<se::EnvironmentComponent>(_PointLight);
		_LightEntity.AddComponent<se::NativeScriptComponent>().Bind<se::LightController>();

		se::Entity   _CameraEntity = CreateEntity();
		_CameraEntity.AddComponent<se::CameraComponent>(_MainCamera);
		_CameraEntity.AddComponent<se::NativeScriptComponent>().Bind<se::FreeCameraController>();
	}

	CreateLayer<MainLayer>("MainLayer");
	InitLayer("MainLayer");
	//InitLayers();
}
	
void MainScene::OnUpdate(const se::Timer& deltaTime)
{
	{
		UpdateNativeScripts(deltaTime); // Can be moved to layer specific object ?
	}

	for (auto& layer : GetLayers())
	{
		if (layer->IsActive())
			layer->OnUpdate(deltaTime);
	}
}

void MainScene::OnRender()
{
	for (auto& layer : GetLayers())
	{
		if (layer->IsActive())
			layer->OnRender();
	}
}

void MainScene::OnDelete()
{
	// Delete Camera and light jsut for now here
	{
		auto _Lights = GetEntities().view<se::EnvironmentComponent>();
		delete _Lights.get<se::EnvironmentComponent>(_Lights[0]).Instance;
	}
	{
		/*auto _Camera = GetRegistry().view<se::CameraComponent>();
		delete _Camera.get<se::CameraComponent>(_Camera[0]).Camera;*/
	}
}
