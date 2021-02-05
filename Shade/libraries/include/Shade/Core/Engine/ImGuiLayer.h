#pragma once
#include "Shade/Core/Engine/Layer.h"
#include <ImGui/imgui.h>


struct ImGuiViewport;

namespace se
{
	
	class SE_API ImGuiLayer : public se::Layer
	{
	public:
		ImGuiLayer(const std::string& name, se::Scene* scene);
		virtual ~ImGuiLayer();

		virtual void OnCreate() override;
		virtual void OnInit() override;
		virtual void OnUpdate(const se::Timer& deltaTime) override;
		virtual void OnRenderBegin() override;
		virtual void OnRender() = 0;
		virtual void OnRenderEnd() override;
		virtual void OnDelete() = 0;	
	protected:
		int m_WindowFlags;
		int m_DockSpaceFlags;
		ImGuiViewport* m_Viewport;
		void ShowDemoWindow();
	};
}

