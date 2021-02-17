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
		virtual void OnEvent(const se::Event& event) = 0;
		void OnImGuiEvent(const se::Event& event);
	protected:
		int m_WindowFlags;
		int m_DockSpaceFlags;
		ImGuiViewport* m_Viewport;
		ImGuizmo::OPERATION m_GuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		void ShowDemoWindow();
		static void DrawVec3(const std::string& label, glm::vec3& values, const float& min =-FLT_MAX, const float& max = FLT_MAX, const float& reset = 0.0, const float& cw1 = 100.0f, const float& cw2 = 0);
		bool DrawDragFloat(const std::string& label, float& values, const float& reset = 0.0f, const float& cw1 = 100.0f, const float& cw2 = 0);
		void DrawColor3(const std::string& label, glm::vec3& values, const float& cw1 = 100.0f, const float& cw2 = 0);
		void PushItemFlag(int option);
		void PopItemFlag();
		bool ShowImGuizmo(glm::mat4& transform, const se::Camera* camera, const bool& show, const float& x, const float& y, const float& w, const float& h);
		void ShowFPSOverlay(ImGuiViewport* viewport, const bool& show, const float& x, const float& y);

		ImVec2 CalcItemSize(ImVec2 size, float default_w, float default_h);
	private:
		void SetupImGuiStyle(bool bStyleDark_, float alpha_);
	};
}

