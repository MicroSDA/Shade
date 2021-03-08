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

}

void MainLayer::OnInit()
{
	se::Renderer::Enable(GL_CULL_FACE);
	se::Renderer::Enable(GL_DEPTH_TEST);

	se::FramebufferSpec spec(100, 100, { se::FrameBufferTextureFormat::RGBA8, se::FrameBufferTextureFormat::Depth });
	GetScene()->CreateFrameBuffer("MainLayerFB", spec);

	m_BasicModelShader  = se::ShadeShared<se::Shader>(se::Shader::CreateFromFile("resources/shaders/BasicModel.bin"));
	m_GridShader		= se::ShadeShared<se::Shader>(se::Shader::CreateFromFile("resources/shaders/Grid.bin"));
	m_TextShader		= se::ShadeShared<se::Shader>(se::Shader::CreateFromFile("resources/shaders/Text.bin"));
	//Shader's layouts
	m_BasicModelShader->SetLayout([](const void* entity, const se::Shader* shader) {
		shader->SendUniformMatrix4Float("ModelMatrix", GL_FALSE, static_cast<const se::Transform3DComponent*>(entity)->Transform.GetModelMatrix());
		});
	m_GridShader->SetLayout([](const void* entity, const se::Shader* shader) {
		shader->SendUniformMatrix4Float("ModelMatrix", GL_FALSE, static_cast<const se::Transform3DComponent*>(entity)->Transform.GetModelMatrix());
		});
	m_TextShader->SetLayout([](const void* entity, const se::Shader* shader) {
		shader->SendUniformMatrix4Float("ModelMatrix", GL_FALSE, static_cast<const se::Transform3DComponent*>(entity)->Transform.GetModelMatrix());
		});
}

void MainLayer::OnUpdate(const se::Timer& deltaTime)
{
}

void MainLayer::OnRender()
{

	auto camera = GetScene()->GetActiveCamera();
	if (camera != nullptr)
	{
		m_BasicModelShader->Bind();
		m_BasicModelShader->SendCamera(camera);

		GetScene()->GetEntities().view<se::EnvironmentComponent>().each([&](auto entityId, se::EnvironmentComponent& env_comp)
			{
				env_comp.Environment->Process(m_BasicModelShader.get());
			});
		// Models 
		GetScene()->GetEntities().view<se::Model3DComponent, se::Transform3DComponent>().each([&](
			auto entityId, se::Model3DComponent& model_comp, se::Transform3DComponent& transf_comp)
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
		//Grid
		m_GridShader->Bind();
		m_GridShader->SendCamera(camera);
		se::Application::GetApplication().GetEntities().view<se::DrawableComponent, se::Transform3DComponent>().each([&](
			auto entityId, se::DrawableComponent& drawable_comp, se::Transform3DComponent& transf_comp)
			{
				m_GridShader->Process(&transf_comp);
				se::Renderer::DrawIndexed(*drawable_comp.Drawable);
			});
	}


	m_TextShader->Bind();
	GetScene()->GetEntities().view<se::DrawableTextComponent>().each([&](
		auto entityId, se::DrawableTextComponent& text_comp)
		{
			se::Transform3D transform;
			m_TextShader->Process(&transform);
			se::Renderer::BindTexture(text_comp.Text->GetFont()->GetAtlas());
			se::Renderer::DrawIndexed(*text_comp.Text);
		});

	//auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.Text");
	/*auto texts = GetScene()->GetEntities().view<se::DrawableTextComponent>();
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
	}*/

	//se::Renderer::Disable(GL_BLEND);
}

void MainLayer::OnDelete()
{
}

void MainLayer::OnEvent(const se::Event& event)
{

	/*if (event.GetType() == se::Event::Type::Window)
	{
		if (event.GetWindow() == se::Event::Window::Resized)
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
	}*/
}

void MainLayer::OnRenderBegin()
{
	auto frameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");
	frameBuffer->Bind();
	frameBuffer->Clear();
	//frameBuffer->ClearTextureAttachment(1, -1);
}

void MainLayer::OnRenderEnd()
{
	auto frameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");
	frameBuffer->UnBind();
}
