#pragma once
#include "Shade/Core/Engine/Layer.h"

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
		virtual void OnRender() override;
		virtual void OnRenderEnd() override;
		virtual void OnDelete() override;	
	private:
		int m_WindowFlags;
		int m_DockSpaceFlags;
		ImGuiViewport* m_Viewport;

		void ShowEntities();
		void ShowVewPort();
		void ShowAssetList();
	};
}

