#include "stdafx.h"
#include "ImGuiLayer.h"
#include "ImGui/imgui_internal.h"
#include <ImGui/backends/imgui_impl_opengl3.h>
#include <ImGui/backends/imgui_impl_sdl.h>


namespace se
{
	ImGuiLayer::ImGuiLayer(const std::string& name, se::Scene* scene) : se::Layer(name, scene)
	{
		ImGui::CreateContext();
		SetupImGuiStyle(true, false);

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.DisplaySize = ImVec2((float)se::WindowManager::GetWindow().Width, (float)se::WindowManager::GetWindow().Height);
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
		
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			//style.WindowRounding = 0.0f;
			//style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplSDL2_InitForOpenGL(se::WindowManager::GetWindow().Handler, se::WindowManager::GetContext());
		ImGui_ImplOpenGL3_Init("#version 440");


		m_WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		m_WindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		m_DockSpaceFlags = ImGuiDockNodeFlags_None;

		m_Viewport = ImGui::GetMainViewport();

	
		se::EventManager::RegLayerEventCallback(se::EventType::SDL_WINDOWEVENT, GetScene(), this,
			[&](se::Event const& event) {
				ImGui_ImplSDL2_ProcessWindowEvent(&event);

				return false;
			});
		se::EventManager::RegLayerEventCallback(se::EventType::SDL_KEYDOWN, GetScene(), this,
			[&](se::Event const& event) {
				ImGui_ImplSDL2_ProcessKeyDownUpEvent(&event);

				return false;
			});
		se::EventManager::RegLayerEventCallback(se::EventType::SDL_KEYUP, GetScene(), this,
			[&](se::Event const& event) {
				ImGui_ImplSDL2_ProcessKeyDownUpEvent(&event);

				return false;
			});
		se::EventManager::RegLayerEventCallback(se::EventType::SDL_MOUSEMOTION, GetScene(), this,
			[&](se::Event const& event) {
				ImGui_ImplSDL2_ProcessMouseButtonEvent(&event);

				return false;
			});
		se::EventManager::RegLayerEventCallback(se::EventType::SDL_MOUSEWHEEL, GetScene(), this,
			[&](se::Event const& event) {
				ImGui_ImplSDL2_ProcessMouseWheelEvent(&event);

				return false;
			});
		se::EventManager::RegLayerEventCallback(se::EventType::SDL_TEXTINPUT, GetScene(), this,
			[&](se::Event const& event) {
				ImGui_ImplSDL2_ProcessTexInputEvent(&event);

				return false;
			});

		se::Entity _VeiwPort = GetScene()->CreateEntity("MainSceneDocViewPort");
		_VeiwPort.AddComponent<glm::fvec2>();

		SetupImGuiStyle(true, true);
	}

	ImGuiLayer::~ImGuiLayer()
	{
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnCreate()
	{
		
	}
	void ImGuiLayer::OnInit()
	{

	}
	void ImGuiLayer::OnUpdate(const se::Timer& deltaTime)
	{


	}

	void ImGuiLayer::OnRenderBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(se::WindowManager::GetWindow().Handler);
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();

		ImGui::SetNextWindowPos(m_Viewport->GetWorkPos());
		ImGui::SetNextWindowSize(m_Viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(m_Viewport->ID);
	}

	void ImGuiLayer::OnRenderEnd()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}
	}

	void ImGuiLayer::ShowDemoWindow()
	{
		ImGui::ShowDemoWindow();
	}

	void ImGuiLayer::SetupImGuiStyle(bool bStyleDark_, float alpha_)
	{
		// cherry colors, 3 intensities
#define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
// backgrounds (@todo: complete with BG_MED, BG_LOW)
#define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
// text
#define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = TEXT(0.78f);
		style.Colors[ImGuiCol_TextDisabled] = TEXT(0.28f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		//style.Colors[ImGuiCol_ChildWindowBg] = BG(0.58f);
		style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = BG(1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
		style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
		style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
		style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
		style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
		style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
		style.Colors[ImGuiCol_Header] = MED(0.76f);
		style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
		style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);
		//style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
		//style.Colors[ImGuiCol_ColumnHovered] = MED(0.78f);
		//style.Colors[ImGuiCol_ColumnActive] = MED(1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
		style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
		style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
		style.Colors[ImGuiCol_PlotLines] = TEXT(0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = TEXT(0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
		// [...]
		//style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

		style.WindowPadding = ImVec2(6, 4);
		style.WindowRounding = 6.0f;
		style.FramePadding = ImVec2(5, 2);
		style.FrameRounding = 3.0f;
		style.ItemSpacing = ImVec2(7, 1);
		style.ItemInnerSpacing = ImVec2(1, 1);
		style.TouchExtraPadding = ImVec2(0, 0);
		style.IndentSpacing = 6.0f;
		style.ScrollbarSize = 12.0f;
		style.ScrollbarRounding = 16.0f;
		style.GrabMinSize = 20.0f;
		style.GrabRounding = 2.0f;

		style.WindowTitleAlign.x = 0.50f;

		style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
		style.FrameBorderSize = 0.0f;
		style.WindowBorderSize = 1.0f;
	}
	
	void ImGuiLayer::DrawVec3(const std::string& label, glm::vec3& values, const float& reset, const float& columnWidth)
	{
	
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
		if (ImGui::Button("X", buttonSize)) { values.x = reset; }
		
	
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		if (ImGui::Button("Y", buttonSize)){ values.y = reset; }
			
	
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		if (ImGui::Button("Z", buttonSize)) { values.z = reset; }
		
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}
	void ImGuiLayer::DrawDragFloat(const std::string& label, float& values, const float& reset, const float& columnWidth)
	{
		ImGui::PushID(label.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
		ImGui::DragFloat("##value", &values);
		ImGui::PopItemWidth();
		ImGui::Columns(1);
		ImGui::PopID();
	}
	void ImGuiLayer::DrawColor3(const std::string& label, glm::vec3& values, const float& columnWidth)
	{

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
		ImGui::ColorEdit3("##color", &values[0]);
		ImGui::PopItemWidth();
		ImGui::Columns(1);
		ImGui::PopID();
	}
}