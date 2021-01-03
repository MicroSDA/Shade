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
	se::Renderer::Enable(GL_CULL_FACE);
	se::Renderer::Enable(GL_DEPTH_TEST);
}

void MainLayer::OnUpdate(const se::Timer& deltaTime)
{
	/*auto entities = GetScene()->GetRegistry().view<se::TransformComponent, se::Model3DComponent>();
	for (auto& entity : entities) {
		 auto& transform = entities.get<se::TransformComponent>(entity).Transform;
	}*/
}

void MainLayer::OnRender()
{
	auto _Entities    = GetScene()->GetRegistry().view<se::Model3DComponent, se::RenderComponent, se::ShaderComponent>();
	auto _Enviroments = GetScene()->GetRegistry().view<se::EnvironmentComponent>();
	for (auto& _Entity : _Entities) {
		_Entities.get<se::RenderComponent>(_Entity).Callback(se::Entity(_Entity, GetScene()));
		 auto* _Model = _Entities.get<se::Model3DComponent>(_Entity).Model3D;

		 for (auto& _Enviroment : _Enviroments)
		 {
			 _Enviroments.get<se::EnvironmentComponent>(_Enviroment).Instance->Process(_Entities.get<se::ShaderComponent>(_Entity).Shader);
		 }

		 for (auto& _Mesh: _Model->m_Meshes)
		 {
			 _Mesh.TexturesBind();
			 se::Renderer::Draw(_Mesh);
			 _Mesh.TexturesUnBind();
		 }
	}
}

void MainLayer::OnDelete()
{
	
}
