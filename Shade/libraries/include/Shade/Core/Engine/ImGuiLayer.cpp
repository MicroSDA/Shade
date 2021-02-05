#include "stdafx.h"
#include "ImGuiLayer.h"

#include <ImGui/backends/imgui_impl_opengl3.h>
#include <ImGui/backends/imgui_impl_sdl.h>


namespace se
{
	ImGuiLayer::ImGuiLayer(const std::string& name, se::Scene* scene) : se::Layer(name, scene)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.DisplaySize = ImVec2((float)se::WindowManager::GetWindow().Width, (float)se::WindowManager::GetWindow().Height);
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
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

}