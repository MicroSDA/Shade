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
	auto* _Shader = se::AssetManager::Get<se::Shader>("Assets.Shaders.BasicModel");
	auto* _MainCamera = GetScene()->GetMainCamera();

	_Shader->Bind();
	_Shader->SendUniformMatrix4Float("ViewM",       GL_FALSE, _MainCamera->GetView());
	_Shader->SendUniformMatrix4Float("ProjectionM", GL_FALSE, _MainCamera->GetProjection());
	_Shader->SendUniform3Float("CameraPosition",              _MainCamera->GetPosition());

	{
		auto _Enviroments = GetScene()->GetRegistry().view<se::EnvironmentComponent>();
		for (auto& _Enviroment : _Enviroments)
		{
			_Enviroments.get<se::EnvironmentComponent>(_Enviroment).Instance->Process(_Shader);
		}
	}
	{
		auto _Entities = GetScene()->GetRegistry().view<se::Model3DComponent, se::TransformComponent>();
		for (auto& _Entity : _Entities) {

			auto* _Model = _Entities.get<se::Model3DComponent>(_Entity).Model3D;
			_Shader->SendUniformMatrix4Float("ModelM", GL_FALSE, _Entities.get<se::TransformComponent>(_Entity).Transform.GetModel());

			for (auto& _Mesh : _Model->m_Meshes)
			{
				_Mesh.GetMaterial().Process(_Shader);
				_Mesh.TexturesBind();
				se::Renderer::Draw(_Mesh);
				_Mesh.TexturesUnBind();
			}
		}
	}
	
}

void MainLayer::OnDelete()
{

}
