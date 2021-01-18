#include "stdafx.h"
#include "GuiLayer.h"

GuiLayer::GuiLayer(const std::string& name, se::Scene* scene) : se::Layer(name, scene)
{
}

GuiLayer::~GuiLayer()
{
}

void GuiLayer::OnCreate()
{
}

void GuiLayer::OnInit()
{
}

void GuiLayer::OnUpdate(const se::Timer& deltaTime)
{
}

void GuiLayer::OnRender()
{
	{
		//Grid// TODO move to another layer i guess
		auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.Grid", true);
		_Shader->Bind();
		_Shader->SendUniformMatrix4Float("ViewMatrix", GL_FALSE, this->GetScene()->GetMainCamera()->GetView());
		_Shader->SendUniformMatrix4Float("ProjectionMatrix", GL_FALSE, this->GetScene()->GetMainCamera()->GetProjection());

		auto _Entities = GetScene()->GetEntities().view<se::DrawableComponent, se::Transform3DComponent>();
		for (auto& _Entity : _Entities) {
			_Shader->SendUniformMatrix4Float("ModelMatrix", GL_FALSE, _Entities.get<se::Transform3DComponent>(_Entity).Transform.GetModelMatrix());
			se::Renderer::DrawIndexed(_Shader.get(), *_Entities.get<se::DrawableComponent>(_Entity).Drawable);
		}

	}
	{
		//GUI // TODO move to another layer i guess
		auto _Shader = se::AssetManager::Hold<se::Shader>("Shaders.Sprite", true);
		_Shader->Bind();
		auto _Entities = GetScene()->GetEntities().view<se::Transform2DComponent, se::SpriteComponent>();
		for (auto& _Entity : _Entities) {
			_Shader->SendUniformMatrix4Float("ModelMatrix", GL_FALSE, _Entities.get<se::Transform2DComponent>(_Entity).Transform.GetModelMatrix());

			se::Renderer::Disable(GL_DEPTH_TEST);
				se::Renderer::Enable(GL_BLEND);
				se::Renderer::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				_Entities.get<se::SpriteComponent>(_Entity).Sprite->GetEntities().get<se::TextureComponent>(entt::entity(0)).Texture->Bind(0);
				se::Renderer::DrawNotIndexed(_Shader.get(), *_Entities.get<se::SpriteComponent>(_Entity).Sprite);
				se::Renderer::Disable(GL_BLEND);
			se::Renderer::Enable(GL_DEPTH_TEST);
		}
	}
}

void GuiLayer::OnDelete()
{
}
