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
					this->GetEntities().destroy(model);
					
				}	
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_E)
				se::AssetManager::Free("Shaders.BasicModel");

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

			if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
			{
				std::string str = m_Text.GetText();
				if(str.size())
					str.pop_back();

				m_Text.SetText(str);
			}
			else
			{
				std::string s;
				s.push_back((char)event.key.keysym.sym);
				m_Text.SetText(m_Text.GetText() + s);
			}

			return false;
		});

	
	se::Renderer::SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);
}

void MainScene::OnInit()
{
	
	/*se::Camera* _MainCamera = new se::Camera();
	_MainCamera->SetPosition(0, 3, -5);
	SetMainCamera(_MainCamera);

	se::Entity   _CameraEntity = CreateEntity();
	_CameraEntity.AddComponent<se::CameraComponent>(_MainCamera);
	_CameraEntity.AddComponent<se::NativeScriptComponent>().Bind<se::FreeCameraController>();

	se::Entity _GridEntity = this->CreateEntity("Grid");
	_GridEntity.AddComponent<se::Transform3DComponent>();

	_GridEntity.AddComponent<se::DrawableComponent>(se::ShadeShared<se::Drawable>(new se::Grid(1000, 1000, 100)));

	{// Assets
		auto _Floor	     = se::AssetManager::Hold<se::Model3D>("Models.Floor", false);
		auto _Cube	     = se::AssetManager::Hold<se::Model3D>("Models.Cube" , false);
		auto _Skull	     = se::AssetManager::Hold<se::Model3D>("Models.SamuraiHelmet", false);

		se::Entity _FloorEntity = CreateEntity("Floor");
		_FloorEntity.AddComponent<se::Transform3DComponent>();
		_FloorEntity.AddComponent<se::Model3DComponent>(_Floor);

		se::Entity _CubeEntity = CreateEntity("Cube");
		_CubeEntity.AddComponent<se::Transform3DComponent>().Transform.SetPostition(glm::vec3(5, 1, 2));
		_CubeEntity.AddComponent<se::Model3DComponent>(_Cube);

		{
			se::Entity _SamuraiEntity = CreateEntity("Samurai");
			se::Transform3D _Transform;
			_Transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
			_Transform.SetPostition(glm::vec3(0.0f, 2, 2));
			_SamuraiEntity.AddComponent<se::Transform3DComponent>(_Transform);
			_SamuraiEntity.AddComponent<se::Model3DComponent>(_Skull);
			_SamuraiEntity.AddComponent<se::NativeScriptComponent>().Bind<se::Mode3DController>();

			auto meshes = _SamuraiEntity.GetComponent<se::Model3DComponent>().Model3D->GetEntities().view<se::MeshComponent, se::MaterialComponent>();
			for (auto& mesh : meshes)
			{
				meshes.get<se::MaterialComponent>(mesh).Material.SetShinines(3);
				meshes.get<se::MaterialComponent>(mesh).Material.SetShininesStrength(1);	
				meshes.get<se::MaterialComponent>(mesh).Material.SetDiffuseColor(1.5, 1.5, 1.5);
			}

		}
		{   // Just for Fun )
			auto _POEInterfaceSprite = se::AssetManager::Hold<se::Sprite>("Sprites.PoeImage");
			se::Entity _SpriteEntity = CreateEntity();

			se::Transform2D _Transform;
			_Transform.SetScale(1.0f, 0.20f);
			_Transform.SetPostition(0.0f, - 0.8f);
			_SpriteEntity.AddComponent<se::Transform2DComponent>(_Transform);
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
		_GeneraLight->SetAmbientColor(0.1f, 0.1f, 0.1f);
		_GeneraLight->SetDiffuseColor(0.8f, 0.8f, 0.7f);
		_GeneraLight->SetSpecularColor(0.8f, 0.8f, 0.7f);
		
		
		se::Entity _LightEntity = CreateEntity();
		_LightEntity.AddComponent<se::EnvironmentComponent>(_PointLight);
		_LightEntity.AddComponent<se::NativeScriptComponent>().Bind<se::LightController>();

	
	
	}*/

	//CreateLayer<MainLayer>("MainLayer");
	//CreateLayer<GuiLayer>("GuiLayer");
	//InitLayer("MainLayer");
	//InitLayer("GuiLayer");
	//InitLayers();

	m_Text.SetText("Alena");
}
	
void MainScene::OnUpdate(const se::Timer& deltaTime)
{
	// TODO Change calculatin model matrix, get new matrix every set pos, scale or rotate; and add z rotation to 2dmatrix
	//m_Text.SetText(std::to_string( 1 / deltaTime));

	se::Renderer::Enable(GL_BLEND);
	se::Renderer::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.Text", true);
	se::Transform2D transform;
	transform.SetPostition(500.0, (float)se::WindowManager::GetWindow().Height);
	//transform.SetScale(0.001, 0.001);
	_Shader->Bind();

	float aspect = (float)se::WindowManager::GetWindow().Width / (float)se::WindowManager::GetWindow().Height;
	glm::mat4 projection = glm::ortho(0.0f, (float)se::WindowManager::GetWindow().Width, 0.0f, (float)se::WindowManager::GetWindow().Height);
	_Shader->SendUniformMatrix4Float("ModelMatrix", false, projection * transform.GetModelMatrix());
	
	m_Text.Render();
	/*if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_Q))
	{
		se::Renderer::PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		se::Renderer::PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//se::Renderer::Disable(GL_DEPTH_TEST);
	se::Renderer::Enable(GL_BLEND);

	se::Renderer::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.Text", true);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(se::WindowManager::GetWindow().Width), 0.0f, static_cast<float>(se::WindowManager::GetWindow().Height));
	_Shader->Bind();
	_Shader->SendUniformMatrix4Float("ModelMatrix", false, projection);
	m_Text.Render(std::to_string((int) (1 / (deltaTime ))), 10, 10, 2, glm::vec3(1, 1, 1));
	se::Renderer::Disable(GL_BLEND);*/
	//se::Renderer::Enable(GL_DEPTH_TEST);

	
}

void MainScene::OnRender()
{

}

void MainScene::OnDelete()
{
	
}
