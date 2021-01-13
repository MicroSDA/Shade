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
	auto* _MainCamera = GetScene()->GetMainCamera();
	{
		// Modles 
		auto* _Shader = se::AssetManager::Get<se::Shader>("Assets.Shaders.BasicModel");

		_Shader->Bind();
		_Shader->SendUniformMatrix4Float("ViewM", GL_FALSE, _MainCamera->GetView());
		_Shader->SendUniformMatrix4Float("ProjectionM", GL_FALSE, _MainCamera->GetProjection());
		_Shader->SendUniform3Float("CameraPosition", _MainCamera->GetPosition());

		{
			auto _Enviroments = GetScene()->GetEntities().view<se::EnvironmentComponent>();
			for (auto& _Enviroment : _Enviroments)
			{
				_Enviroments.get<se::EnvironmentComponent>(_Enviroment).Environment->Process(_Shader);
			}
		}
		{
			auto _Entities = GetScene()->GetEntities().view<se::Model3DComponent, se::Transform3DComponent>();
			for (auto& _Entity : _Entities) {

				auto* _Model = _Entities.get<se::Model3DComponent>(_Entity).Model3D;
				_Shader->SendUniformMatrix4Float("ModelM", GL_FALSE, _Entities.get<se::Transform3DComponent>(_Entity).Transform.GetModel());

				auto _MesheEntities = _Model->GetEntities().view<se::MeshComponent, se::MaterialComponent>();
				for (auto& _MeshEnity : _MesheEntities)
				{
					auto& _Mesh     = _MesheEntities.get<se::MeshComponent>(_MeshEnity).Mesh;
					auto& _Material = _MesheEntities.get<se::MaterialComponent>(_MeshEnity).Material;
					_Material.Process(_Shader);

					auto _TexturesEntities = _Mesh->GetEntities().view<se::TextureComponent>();
					for (auto& _TextureEnity : _TexturesEntities)
					{
						_TexturesEntities.get<se::TextureComponent>(_TextureEnity).Texture->Bind(static_cast<GLuint>(_TextureEnity));
					}

					se::Renderer::DrawIndexed(*_Mesh);

					for (auto& _TextureEnity : _TexturesEntities)
					{
						se::Texture::UnBind(static_cast<GLuint>(_TextureEnity));
					}
				}
			}
		}
	}
	{
		
		
	}
	{
		
	}
	
}

void MainLayer::OnDelete()
{

}
