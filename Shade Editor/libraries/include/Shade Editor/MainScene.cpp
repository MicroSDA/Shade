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
				auto models = this->GetEntities().view<se::Model3DComponent>();
				for (auto& model : models)
				{
					auto meshes = models.get<se::Model3DComponent>(model).Model3D->GetEntities().view<se::MeshComponent>();
					for (auto& mesh : meshes)
					{
						meshes.get<se::MeshComponent>(mesh).Mesh->GetEntities().clear<se::TextureComponent>();
					}
				}	
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
			{
				auto entities = this->GetEntities().view<se::TagComponent>();
				for (auto& entity : entities)
				{
					if(entities.get<se::TagComponent>(entity).Tag == "Cube")
						this->GetEntities().destroy(entity);
				}
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				auto* _Layer = this->GetLayer("GuiLayer");
				if (_Layer->IsActive())
					_Layer->SetActive(false);
				else
				_Layer->SetActive(true);
				
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

	se::Entity _GridEntity = this->CreateEntity("Grid");
	_GridEntity.AddComponent<se::Transform3DComponent>();
	_GridEntity.AddComponent<se::DrawableComponent>(new se::Grid(40, 40, 8));


	{// Assets
		auto _Floor	     = se::AssetManager::Hold<se::Model3D>("Assets.Models.Floor");
		auto _Cube	     = se::AssetManager::Hold<se::Model3D>("Assets.Models.Cube");
		auto _Samurai	 = se::AssetManager::Hold<se::Model3D>("Assets.Models.SamuraiHelmet");

		se::Entity _FloorEntity = CreateEntity("Floor");
		_FloorEntity.AddComponent<se::Transform3DComponent>();
		_FloorEntity.AddComponent<se::Model3DComponent>(_Floor);

		se::Entity _CubeEntity = CreateEntity();
		_CubeEntity.AddComponent<se::Transform3DComponent>().Transform.SetPostition(glm::vec3(5, 1, 2));
		_CubeEntity.AddComponent<se::Model3DComponent>(_Cube);

		{
			se::Entity _SamuraiEntity = CreateEntity("Samurai");
			se::Transform3D _Transform;
			_Transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
			_Transform.SetPostition(glm::vec3(0.0f, 2, 2));
			_SamuraiEntity.AddComponent<se::Transform3DComponent>(_Transform);
			_SamuraiEntity.AddComponent<se::Model3DComponent>(_Samurai);
			_SamuraiEntity.AddComponent<se::NativeScriptComponent>().Bind<se::Mode3DController>();
		}
		{   // Just for Fun )
			auto _POEInterfaceSprite = se::AssetManager::Hold<se::Sprite>("Assets.Sprites.PoeImage");
			_POEInterfaceSprite->Init();
			se::Entity _SpriteEntity = CreateEntity();

			se::Transform2D _Transform;
			_Transform.SetScale(1.0f, 0.20f);
			_Transform.SetPostition(0.0f, - 0.8f);

			_SpriteEntity.AddComponent<se::Transform2DComponent>(_Transform);
			//_SpriteEntity.AddComponent<se::TextureComponent>(se::AssetManager::Hold<se::Texture>("Assets.Images.Image"));
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
		
		se::EnvironmentComponent _C = _PointLight;
		se::Entity _LightEntity = CreateEntity();

		_LightEntity.AddComponent<se::EnvironmentComponent>(_C);
		_LightEntity.AddComponent<se::NativeScriptComponent>().Bind<se::LightController>();

		se::Entity _LightEntity2 = CreateEntity();
		_LightEntity2.AddComponent<se::EnvironmentComponent>(_C);
		_LightEntity2.AddComponent<se::NativeScriptComponent>().Bind<se::LightController>();

		se::Entity   _CameraEntity = CreateEntity();
		_CameraEntity.AddComponent<se::CameraComponent>(_MainCamera);
		_CameraEntity.AddComponent<se::NativeScriptComponent>().Bind<se::FreeCameraController>();
	}

	CreateLayer<MainLayer>("MainLayer");
	CreateLayer<GuiLayer>("GuiLayer");
	InitLayer("MainLayer");
	InitLayer("GuiLayer");
	//InitLayers();
}
	
void MainScene::OnUpdate(const se::Timer& deltaTime)
{
	{
		UpdateNativeScripts(deltaTime); // Can be moved to layer specific object ?
	}


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
