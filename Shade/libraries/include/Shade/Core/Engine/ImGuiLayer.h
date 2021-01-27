#pragma once
#include "Shade/Core/Engine/Layer.h"

namespace se
{
	class SE_API ImGuiLayer : public se::Layer
	{
	public:
		ImGuiLayer(const std::string& name, se::Scene* scene);
		~ImGuiLayer();

		virtual void OnCreate() override;
		virtual void OnInit() override;
		virtual void OnUpdate(const se::Timer& deltaTime) override;
		virtual void OnRender() override;
		virtual void OnDelete() override;
	};
}

