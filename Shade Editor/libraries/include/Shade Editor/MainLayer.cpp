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
	se::EventManager::RegLayerEventCallback(se::EventType::SDL_WINDOWEVENT, GetScene(), this,
		[&](se::Event const& event) {
		
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				auto _ViewPortSize = GetScene()->GetEntities().view<glm::fvec2, se::TagComponent>();
				
				for (auto& _ViewPort : _ViewPortSize)
				{
					if (_ViewPortSize.get<se::TagComponent>(_ViewPort).Tag == "MainSceneDocViewPort")
					{
						auto _FrameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");

						if (_FrameBuffer)
							_FrameBuffer->Resize(_ViewPortSize.get<glm::vec2>(_ViewPort).x, _ViewPortSize.get<glm::vec2>(_ViewPort).y);
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

	se::FramebufferSpec fbSpec( 100,100, { se::FrameBufferTextureFormat::RGBA8, se::FrameBufferTextureFormat::Depth });
	GetScene()->CreateFrameBuffer("MainLayerFB", fbSpec);
}

void MainLayer::OnUpdate(const se::Timer& deltaTime)
{
	
}

void MainLayer::OnRender()
{
	auto* _MainCamera = GetScene()->GetMainCamera();
	{
		// Modles 
		auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.BasicModel", true);

		_Shader->Bind();
		_Shader->SendUniformMatrix4Float("ViewMatrix", GL_FALSE, _MainCamera->GetView());
		_Shader->SendUniformMatrix4Float("ProjectionMatrix", GL_FALSE, _MainCamera->GetProjection());
		_Shader->SendUniform3Float("CameraPosition", _MainCamera->GetPosition());
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
	}

	auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.Text", true);
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

	se::Renderer::Disable(GL_BLEND);
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
	}
}

void MainLayer::OnRenderEnd()
{
	auto _FrameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");
	if (_FrameBuffer)
		_FrameBuffer->UnBind();
}
