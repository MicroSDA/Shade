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

	se::Renderer::Enable(GL_CULL_FACE);
	se::Renderer::Enable(GL_DEPTH_TEST);
}

void MainLayer::OnUpdate(const se::Timer& deltaTime)
{
	auto entities = GetScene()->GetRegistry().view<se::TransformComponent, se::Model3DComponent>();
	for (auto& entity : entities) {

		auto& transform = entities.get<se::TransformComponent>(entity).Transform;
		transform.SetRotation(glm::vec3(transform.GetRotation().x + 2.5f * deltaTime, transform.GetRotation().y + 2.5f * deltaTime, 0));
	}
}

void MainLayer::OnRender()
{
	auto entities = GetScene()->GetRegistry().view<se::Model3DComponent, se::RenderComponent, se::ShaderComponent>();
	for (auto& entity : entities) {

		 entities.get<se::RenderComponent>(entity).Callback(se::Entity(entity, GetScene()));
		 auto* model = entities.get<se::Model3DComponent>(entity).Model3D;
		 for (auto& mesh: model->m_Meshes)
		 {
			se::Renderer::Draw(mesh);
		 }
	}
}

void MainLayer::OnDelete()
{
	
}
