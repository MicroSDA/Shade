#include "stdafx.h"
#include "ModelPreviewLayer.h"

ModelPreviewLayer::ModelPreviewLayer(const std::string& name, se::Scene* scene) : se::Layer(name, scene)
{
}

ModelPreviewLayer::~ModelPreviewLayer()
{
}

void ModelPreviewLayer::OnCreate()
{
}

void ModelPreviewLayer::OnInit()
{
	se::FramebufferSpec spec(100, 100, { se::FrameBufferTextureFormat::RGBA8, se::FrameBufferTextureFormat::Depth });
	GetScene()->CreateFrameBuffer("ModelLayerFB", spec);

	m_BasicModelShader = se::ShadeShared<se::Shader>(se::Shader::CreateFromFile("resources/shaders/BasicModel.bin"));
	m_GridShader = se::ShadeShared<se::Shader>(se::Shader::CreateFromFile("resources/shaders/Grid.bin"));

	//Shader's layouts
	m_BasicModelShader->SetLayout([](const void* entity, const se::Shader* shader) {
		shader->SendUniformMatrix4Float("ModelMatrix", GL_FALSE, static_cast<const se::Transform3DComponent*>(entity)->Transform.GetModelMatrix());
		});
	m_GridShader->SetLayout([](const void* entity, const se::Shader* shader) {
		shader->SendUniformMatrix4Float("ModelMatrix", GL_FALSE, static_cast<const se::Transform3DComponent*>(entity)->Transform.GetModelMatrix());
		});
}

void ModelPreviewLayer::OnRenderBegin()
{
	auto frameBuffer = GetScene()->GetFrameBuffer("ModelLayerFB");
	frameBuffer->Bind();
	frameBuffer->Clear();
}

void ModelPreviewLayer::OnRender()
{
	auto camera = GetScene()->GetActiveCamera();

	if (camera != nullptr)
	{
		m_GridShader->Bind();
		m_GridShader->SendCamera(camera);
		se::Application::GetApplication().GetEntities().view<se::DrawableComponent, se::Transform3DComponent>().each([&](
			auto entityId, se::DrawableComponent& drawable_comp, se::Transform3DComponent& transf_comp)
			{
				m_GridShader->Process(&transf_comp);
				se::Renderer::DrawIndexed(*drawable_comp.Drawable);
			});


		// Models 
		m_BasicModelShader->Bind();
		m_BasicModelShader->SendCamera(camera);

		se::Application::GetApplication().GetEntities().view<se::TagComponent, se::EnvironmentComponent > ().each([&](
			auto entityId, se::TagComponent& tag, se::EnvironmentComponent& env_comp)
			{
				env_comp.Environment->Process(m_BasicModelShader.get());
			});
		
		//se::Renderer::Disable(GL_CULL_FACE);
		//se::Renderer::Enable(GL_BLEND);
		//se::Renderer::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		se::Application::GetApplication().GetEntities().view<se::TagComponent, se::Model3DComponent, se::Transform3DComponent>().each([&](
			auto entityId,se::TagComponent& tag, se::Model3DComponent& model_comp, se::Transform3DComponent& transf_comp)
			{
				if (model_comp.Model3D != nullptr)
				{
					m_BasicModelShader->Process(&transf_comp);
					// Meshes
					model_comp.Model3D->GetEntities().view<se::MeshComponent, se::MaterialComponent>().each([&](
						auto entityId, se::MeshComponent& mesh_comp, se::MaterialComponent& material_comp)
						{
							material_comp.Material.Process(m_BasicModelShader.get());
							// Textures
							mesh_comp.Mesh->GetEntities().view<se::TextureComponent>().each([&](
								auto entityId, se::TextureComponent& texture_comp)
								{
									texture_comp.Texture->Bind(m_BasicModelShader.get(), static_cast<uint32_t>(entityId));
								});

							se::Renderer::DrawIndexed(*mesh_comp.Mesh);
						});
				}
			});
		se::Renderer::Disable(GL_BLEND);
	}
}

void ModelPreviewLayer::OnRenderEnd()
{
	auto frameBuffer = GetScene()->GetFrameBuffer("ModelLayerFB");
	frameBuffer->UnBind();
}

void ModelPreviewLayer::OnUpdate(const se::Timer& deltaTime)
{
}

void ModelPreviewLayer::OnDelete()
{
}

void ModelPreviewLayer::OnEvent(const se::Event& event)
{
	/*if (event.GetType() == se::Event::Type::Window)
	{
		if (event.GetWindow() == se::Event::Window::Resized)
		{
			auto entites = se::Application::GetApplication().GetEntities().view<glm::vec2, se::TagComponent>();

			for (auto& viewPort : entites)
			{
				if (entites.get<se::TagComponent>(viewPort).Tag == "ModelPreveiwViewPort")
				{
					auto size = entites.get<glm::vec2>(viewPort);

					auto activeCamera = se::Application::GetApplication().GetCurrentScene()->GetActiveCamera();
					if (activeCamera != nullptr)
						activeCamera->Resize(size.x / size.y);
						//activeCamera->Resize(size.x / size.y);

					GetScene()->GetFrameBuffer("ModelLayerFB")->Resize(size.x, size.y);
				}
			}
		}
	}*/
}
