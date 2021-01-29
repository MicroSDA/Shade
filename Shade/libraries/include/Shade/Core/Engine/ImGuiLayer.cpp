#include "stdafx.h"
#include "ImGuiLayer.h"



#define IMGUI_IMPL_OPENGL_LOADER_GLAD
//#include <../ImGui/imgui.h>
#include <../ImGui/backends/imgui_impl_opengl3.h>
#include <../ImGui/backends/imgui_impl_sdl.h>


namespace se
{
	ImGuiLayer::ImGuiLayer(const std::string& name, se::Scene* scene) : se::Layer(name, scene)
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnCreate()
	{
		SDL_EventType;
		se::EventManager::RegLayerEventCallback(se::EventType::SDL_WINDOWEVENT, GetScene(), this,
			[&](se::Event const& event)  {
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
		se::EventManager::RegLayerEventCallback(se::EventType::SDL_TEXTINPUT, GetScene(), this,
			[&](se::Event const& event) {
				ImGui_ImplSDL2_ProcessTexInputEvent(&event);

				return false;
			});

		se::Entity _VeiwPort = GetScene()->CreateEntity("MainSceneDocViewPort");
		_VeiwPort.AddComponent<glm::fvec2>();
	}
	void ImGuiLayer::OnInit()
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
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForOpenGL(se::WindowManager::GetWindow().Handler, se::WindowManager::GetContext());
		ImGui_ImplOpenGL3_Init("#version 440");


		m_WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		m_WindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		m_DockSpaceFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_AutoHideTabBar;

		m_Viewport = ImGui::GetMainViewport();

	

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



	void ImGuiLayer::OnRender()
	{
		static bool show = true;

		
		


		ImGui::Begin("DockSpace Demo", &show, m_WindowFlags);

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), m_DockSpaceFlags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New")) {}

				if (ImGui::MenuItem("Open")) {}

				if (ImGui::MenuItem("Save")) {}

				ImGui::Separator();
				if (ImGui::MenuItem("Exit"))  se::Application::GetApplication().Quit();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
		{
		
			ImGui::Begin("Fps");                    
			ImGui::Text("Frame time: %.3f ms \nFps: %.1f", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();

			ImGui::Begin("Editor");
			ImGui::Text("Propertry list");
			ImGui::End();


			ImGui::Begin("Viewport");
			auto _FrameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");
			if (_FrameBuffer)
			{
				auto _ViewPortSize = GetScene()->GetEntities().view<glm::fvec2, se::TagComponent>();

				for (auto& _VeiwPort : _ViewPortSize)
				{
					ImVec2 _ViewportPanelSize = ImGui::GetContentRegionAvail();

					if (_ViewPortSize.get<se::TagComponent>(_VeiwPort).Tag == "MainSceneDocViewPort")
					{
						if (_ViewPortSize.get<glm::fvec2>(_VeiwPort).x != _ViewportPanelSize.x
							|| _ViewPortSize.get<glm::fvec2>(_VeiwPort).y != _ViewportPanelSize.y)
						{
							_ViewPortSize.get<glm::fvec2>(_VeiwPort).x = _ViewportPanelSize.x;
							_ViewPortSize.get<glm::fvec2>(_VeiwPort).y = _ViewportPanelSize.y;

							//Create window resize event and grab it in MainLayer
							se::Event _Event;
							_Event.type = SDL_WINDOWEVENT;
							_Event.window.event = SDL_WINDOWEVENT_RESIZED;
							se::EventManager::PusEvent(_Event);
						}
					}

					ImTextureID tid = reinterpret_cast<void*>(_FrameBuffer->GetTextureAttachment());
					ImGui::Image(tid, ImVec2{ _ViewportPanelSize.x, _ViewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
				}
			}

			ImGui::End();
		}

		ImGui::Begin("Log");
		ImGui::Text("Log");
		ImGui::End();

		ImGui::Begin("Scene");
		ImGui::Text("Scene");
		ImGui::End();
		
		//ImGui::ShowDemoWindow(&show);
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
	void ImGuiLayer::OnDelete()
	{
		ImGui::DestroyContext();
	}
}
