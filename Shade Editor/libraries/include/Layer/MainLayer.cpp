#include "MainLayer.h"

MainLayer::MainLayer(const std::string& name, se::Scene* scene)
	:se::Layer(name, scene)
{
}

MainLayer::~MainLayer()
{
}

void MainLayer::OnCreate()
{

	DEBUG_PRINT("OnLayer Create", se::LogLevel::INFO_PRIMARY);

	e = m_pScene->CreateEntity();
	b = m_pScene->CreateEntity();

	auto* shader = se::AssetManager::Hold<se::Shader>("Assets.Shaders.BasicModel");
	auto* mesh   = se::AssetManager::Hold<se::Mesh>("Assets.Models.Cube");
	auto* camera = new se::Camera(glm::vec3(0.0, 0.0, 0.0), 70.0f, float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), 0.01f, 3000.0f);

	se::RenderLayoutComponent r{ [](se::Entity& entity) {

		auto& transform = entity.GetComponent<se::TransformComponent>().Transform;
		auto* shader    = entity.GetComponent<se::ShaderComponent>().Shader;
		auto* camera    = entity.GetComponent<se::CameraComponent>().Camera;

		shader->Bind();
		shader->SendUniformMatrix4fv(0, GL_FALSE, &transform.GetModel()[0][0]);
		shader->SendUniformMatrix4fv(1, GL_FALSE, &camera->GetView()[0][0]);
		shader->SendUniformMatrix4fv(2, GL_FALSE, &camera->GetPerpective()[0][0]);

		transform.SetRotation(glm::vec3(
			transform.GetRotation().x + 0.05f,
			transform.GetRotation().y + 0.05f,
			transform.GetRotation().z + 0.05f));
	} };

	

	e.AddComponent<se::TransformComponent>(se::Transform()).Transform.SetPostition(glm::vec3(1, 0, 3 + rand() % 5));
	e.AddComponent<se::ShaderComponent>(shader);
	e.AddComponent<se::MeshComponent>(mesh);
	e.AddComponent<se::CameraComponent>(camera);
	e.AddComponent<se::RenderLayoutComponent>(r);

	b.AddComponent<se::TransformComponent>(se::Transform()).Transform.SetPostition(glm::vec3(-1, 0, 3 + rand() % 5));
	b.AddComponent<se::ShaderComponent>(shader);
	b.AddComponent<se::MeshComponent>(mesh);
	b.AddComponent<se::CameraComponent>(camera);
	b.AddComponent<se::RenderLayoutComponent>(r);


	//se::AssetManager::Free("Assets.Shaders.BasicModel");
	
}
void MainLayer::OnInit()
{
	DEBUG_PRINT("OnLayer Init", se::LogLevel::INFO_PRIMARY);

	RegisterEventCallback(se::EventType::SDL_KEYDOWN,
		[](se::Event const& event) {

			if (event.key.keysym.sym == se::KeyCode::SDLK_BACKSPACE)
			{
				DEBUG_PRINT("LayerEvent SDLK_BACKSPACE", se::LogLevel::EVENT);
			}

			return false;
		});
}

void MainLayer::OnRender() 
{
	
	
	

	
	//shader->Bind();
	//se::Render::DrawIndexed(pTriangle);
	
	e.GetComponent<se::RenderLayoutComponent>().Layout(e);
	se::Render::DrawIndexed(e.GetComponent<se::MeshComponent>().Mesh);

	b.GetComponent<se::RenderLayoutComponent>().Layout(b);
	se::Render::DrawIndexed(b.GetComponent<se::MeshComponent>().Mesh);
	//m_pScene->m_Registry.get<se::Mesh>((entt::entity)0u);
}

void MainLayer::OnUpdate() 
{

	//DEBUG_PRINT("OnLayer Update", se::LogLevel::INFO_PRIMARY);
}

void MainLayer::OnDelete()
{
	DEBUG_PRINT("On Layer Delete", se::LogLevel::INFO_PRIMARY);
}
