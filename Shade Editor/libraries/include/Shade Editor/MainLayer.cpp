#include "stdafx.h"
#include "MainLayer.h"
#include "MainScene.h"


MainLayer::MainLayer(const std::string& name, se::Scene* scene) : se::Layer(name, scene)
{
}

MainLayer::~MainLayer()
{

}

void MainLayer::OnCreate()
{
	se::EventManager::RegLayerEventCallback(se::EventType::SDL_WINDOWEVENT, GetScene(), this,
		[&](se::Event const& event) {
		
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				
				auto entites = se::Application::GetApplication().GetEntities().view<glm::vec2, se::TagComponent>();
				
				for (auto& viewPort : entites)
				{
					if (entites.get<se::TagComponent>(viewPort).Tag == "SceneViewPort")
					{
						auto size = entites.get<glm::vec2>(viewPort);

						auto activeCamera = se::Application::GetApplication().GetCurrentScene()->GetActiveCamera();
						if (activeCamera != nullptr)
							activeCamera->Resize(size.x / size.y);

						auto frameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");

						if (frameBuffer)
							frameBuffer->Resize(size.x, size.y);
					}
				}
			}
			
			return false;
		});
}

void MainLayer::OnInit()
{
	se::Renderer::Enable(GL_CULL_FACE);
	se::Renderer::Enable(GL_DEPTH_TEST);

	se::FramebufferSpec fbSpec( 100,100, { se::FrameBufferTextureFormat::RGBA8, se::FrameBufferTextureFormat::RED_INTEGER, se::FrameBufferTextureFormat::Depth });
	GetScene()->CreateFrameBuffer("MainLayerFB", fbSpec);
}

void MainLayer::OnUpdate(const se::Timer& deltaTime)
{
	
}

void MainLayer::OnRender()
{
	auto activeCamera = GetScene()->GetActiveCamera();
	{
		// Modles 
		auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.BasicModel", true);

		_Shader->Bind();
		_Shader->SendUniformMatrix4Float("ViewMatrix", GL_FALSE, activeCamera->GetView());
		_Shader->SendUniformMatrix4Float("ProjectionMatrix", GL_FALSE, activeCamera->GetProjection());
		_Shader->SendUniform3Float("CameraPosition", activeCamera->GetPosition());
		{
			auto _Enviroments = GetScene()->GetEntities().view<se::EnvironmentComponent>();
			for (auto& _Enviroment : _Enviroments)
			{
				_Enviroments.get<se::EnvironmentComponent>(_Enviroment).Environment->Process(_Shader.get());
			}
		}
		{
			auto _Entities = GetScene()->GetEntities().view<se::Model3DComponent, se::Transform3DComponent>();
			for (auto& _Entity : _Entities) {

				auto _Model = _Entities.get<se::Model3DComponent>(_Entity).Model3D;
				_Shader->SendUniformMatrix4Float("ModelMatrix", GL_FALSE, _Entities.get<se::Transform3DComponent>(_Entity).Transform.GetModelMatrix());

				auto _MesheEntities = _Model->GetEntities().view<se::MeshComponent, se::MaterialComponent>();
				for (auto& _MeshEnity : _MesheEntities)
				{
					auto _Mesh     = _MesheEntities.get<se::MeshComponent>(_MeshEnity).Mesh;
					auto& _Material = _MesheEntities.get<se::MaterialComponent>(_MeshEnity).Material;
					_Material.Process(_Shader.get());

					auto _TexturesEntities = _Mesh->GetEntities().view<se::TextureComponent>();
					for (auto& _TextureEnity : _TexturesEntities)
					{
						_TexturesEntities.get<se::TextureComponent>(_TextureEnity).Texture->Bind(static_cast<GLuint>(_TextureEnity));
					}

					se::Renderer::DrawIndexed(*_Mesh);
				}
			}
		}
		{
			//Grid// TODO move to another layer i guess
			auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.Grid", true);
			_Shader->Bind();
			_Shader->SendUniformMatrix4Float("ViewMatrix", GL_FALSE, GetScene()->GetActiveCamera()->GetView());
			_Shader->SendUniformMatrix4Float("ProjectionMatrix", GL_FALSE, GetScene()->GetActiveCamera()->GetProjection());
			_Shader->SendUniform3Float("CameraPosition", GetScene()->GetActiveCamera()->GetPosition());

			auto _Entities = GetScene()->GetEntities().view<se::DrawableComponent, se::Transform3DComponent>();
			for (auto& _Entity : _Entities) {
				_Shader->SendUniformMatrix4Float("ModelMatrix", GL_FALSE, _Entities.get<se::Transform3DComponent>(_Entity).Transform.GetModelMatrix());
			
				se::Renderer::DrawIndexed(*_Entities.get<se::DrawableComponent>(_Entity).Drawable);
			}
		}
	}
	/*auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.Text", true);
	auto texts = GetScene()->GetEntities().view<se::DrawableTextComponent>();
	se::Transform2D transform;
	transform.SetPostition(0.0f, (float)se::WindowManager::GetWindow().Height);
	transform.SetScale(0.8, 0.8);
	_Shader->Bind();
	se::Renderer::Enable(GL_BLEND);
	se::Renderer::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto text : texts)
	{
		glm::mat4 projection = glm::ortho(0.0f, (float)se::WindowManager::GetWindow().Width, 0.0f, (float)se::WindowManager::GetWindow().Height);
		_Shader->SendUniformMatrix4Float("ModelMatrix", false, projection * transform.GetModelMatrix());
		auto& t = texts.get<se::DrawableTextComponent>(text).Text;
		se::Renderer::BindTexture(t->GetFont()->GetAtlas());
		se::Renderer::DrawIndexed(*t);
	}

	se::Renderer::Disable(GL_BLEND);*/
}

void MainLayer::OnDelete()
{
}

void MainLayer::OnRenderBegin()
{
	auto _FrameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");
	if (_FrameBuffer)
	{
		_FrameBuffer->Bind();
		_FrameBuffer->Clear();
		_FrameBuffer->ClearTextureAttachment(1, -1);
	}
}

void MainLayer::OnRenderEnd()
{
	auto _FrameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");
	if (_FrameBuffer)
		_FrameBuffer->UnBind();
}
