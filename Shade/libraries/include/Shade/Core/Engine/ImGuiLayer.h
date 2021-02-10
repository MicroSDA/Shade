#pragma once
#include "Shade/Core/Engine/Layer.h"
#include <ImGui/imgui.h>
#include <ImGizmo/ImGuizmo.h>

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
		ImGuizmo::OPERATION m_GuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		void ShowDemoWindow();
		void DrawVec3(const std::string& label, glm::vec3& values, const float& min =-FLT_MAX, const float& max = FLT_MAX, const float& reset = 0.0, const float& cw1 = 100.0f, const float& cw2 = 0);
		void DrawDragFloat(const std::string& label, float& values, const float& reset = 0.0f, const float& cw1 = 100.0f, const float& cw2 = 0);
		void DrawColor3(const std::string& label, glm::vec3& values, const float& cw1 = 100.0f, const float& cw2 = 0);
	private:
		void SetupImGuiStyle(bool bStyleDark_, float alpha_);
	};
}

