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
		auto _Shader = se::AssetManager::Hold<se::Shader>("Assets.Shaders.Grid");
		_Shader->Bind();
		_Shader->SendUniformMatrix4Float("ViewM", GL_FALSE, this->GetScene()->GetMainCamera()->GetView());
		_Shader->SendUniformMatrix4Float("ProjectionM", GL_FALSE, this->GetScene()->GetMainCamera()->GetProjection());

		auto _Entities = GetScene()->GetEntities().view<se::DrawableComponent, se::Transform3DComponent>();
		for (auto& _Entity : _Entities) {
			_Shader->SendUniformMatrix4Float("ModelM", GL_FALSE, _Entities.get<se::Transform3DComponent>(_Entity).Transform.GetModel());
			//se::Renderer::Disable(GL_DEPTH_TEST);
			se::Renderer::DrawIndexed(*_Entities.get<se::DrawableComponent>(_Entity).Drawable);
			//se::Renderer::Enable(GL_DEPTH_TEST);
		}

	}
	{
		//GUI // TODO move to another layer i guess
		auto _Shader = se::AssetManager::Hold<se::Shader>("Assets.Shaders.Sprite");
		_Shader->Bind();
		auto _Entities = GetScene()->GetEntities().view<se::Transform2DComponent, se::SpriteComponent>();
		for (auto& _Entity : _Entities) {
			_Shader->SendUniformMatrix4Float("ModelM", GL_FALSE, _Entities.get<se::Transform2DComponent>(_Entity).Transform.GetModel());

			se::Renderer::Disable(GL_DEPTH_TEST);
			se::Renderer::Enable(GL_BLEND);
			se::Renderer::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			_Entities.get<se::SpriteComponent>(_Entity).Sprite->GetEntities().get<se::TextureComponent>(entt::entity(0)).Texture->Bind(0);
			se::Renderer::DrawNotIndexed(*_Entities.get<se::SpriteComponent>(_Entity).Sprite);
			se::Renderer::Enable(GL_DEPTH_TEST);
			se::Renderer::Disable(GL_BLEND);

			se::Texture::UnBind(0); // TODO Why ? need test
		}
	}
}

void GuiLayer::OnDelete()
{
}
