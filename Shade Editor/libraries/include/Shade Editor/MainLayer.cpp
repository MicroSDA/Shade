#include "stdafx.h"
#include "MainLayer.h"


MainLayer::MainLayer(const std::string& name, se::Scene* scene) : se::Layer(name, scene)
{
}

MainLayer::~MainLayer()
{
}

void MainLayer::OnCreate()
{
	
}

void MainLayer::OnInit()
{
	se::EventManager::RegLayerEventCallback(se::EventType::SDL_KEYDOWN, GetScene(), this,
		[](const se::Event& event) {
		
			if (event.key.keysym.sym == SDLK_KP_ENTER)
			{
				se::Log::Print("SDLK_KP_ENTER", se::SLCode::Event);
			}

			return false;
		});

	se::Model3D* cube = se::AssetManager::Hold<se::Model3D>("Assets.Models.Cube");
	se::Shader* shader = se::AssetManager::Hold<se::Shader>("Assets.Shaders.BasicModel");
	se::Camera* camera = new se::Camera();
	se::Entity entity = GetScene()->CreateEntity();

	entity.AddComponent<se::TransformComponent>().Transform.SetPostition(glm::vec3(0, 0, 10));
	entity.AddComponent<se::ShaderComponent>(shader);
	entity.AddComponent<se::CameraComponent>(camera);
	entity.AddComponent<se::Model3DComponent>(cube);

	entity.AddComponent<se::RenderComponent>().Layout = [](se::Entity& entity) {

		auto& transform = entity.GetComponent<se::TransformComponent>().Transform;
		auto* shader = entity.GetComponent<se::ShaderComponent>().Shader;
		auto* camera = entity.GetComponent<se::CameraComponent>().Camera;

		shader->Bind();
		shader->SendUniformMatrix4fv(0, GL_FALSE, &transform.GetModel()[0][0]);
		shader->SendUniformMatrix4fv(1, GL_FALSE, &camera->GetView()[0][0]);
		shader->SendUniformMatrix4fv(2, GL_FALSE, &camera->GetPerpective()[0][0]);
	
	};
}

void MainLayer::OnUpdate()
{
	
}

void MainLayer::OnRender()
{
	auto view = GetScene()->GetRegistry().view<se::Model3DComponent, se::RenderComponent>();
	 
	for (auto entity : view) {
		auto* model = view.get<se::Model3DComponent>(entity).Model3D;

		se::Entity e(entity, GetScene());

		view.get<se::RenderComponent>(entity).Layout(e);

		for (auto& mesh: model->m_Meshes)
		{
			mesh.Draw();
		}
	}
	
}

void MainLayer::OnDelete()
{
	
}
