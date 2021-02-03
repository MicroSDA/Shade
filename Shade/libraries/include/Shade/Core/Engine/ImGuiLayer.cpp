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
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplSDL2_InitForOpenGL(se::WindowManager::GetWindow().Handler, se::WindowManager::GetContext());
		ImGui_ImplOpenGL3_Init("#version 440");


		m_WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		m_WindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		m_DockSpaceFlags = ImGuiDockNodeFlags_None;

		m_Viewport = ImGui::GetMainViewport();

		SDL_EventType;
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


			ShowVewPort();
			ShowAssetList();
		}

		ImGui::Begin("Log");
		ImGui::Text("Log");
		ImGui::End();

		ImGui::Begin("Scene");
		ImGui::Text("Scene");
		ImGui::End();

		ImGui::Begin("Lightning sources");
		auto _Lights = GetScene()->GetEntities().view<se::EnvironmentComponent>();
		for (auto& _Light : _Lights)
		{
			ImGui::Text("Lightning sources:");
			ImGui::Separator();
			auto pLight = dynamic_cast<se::Light*>(_Lights.get<se::EnvironmentComponent>(_Light).Environment.get());

			if (pLight)
			{
				float _AmbientColor[3], _DiffuesColor[3], _SpecularColor[3];

				_AmbientColor[0] = pLight->GetAmbientColor().r;
				_AmbientColor[1] = pLight->GetAmbientColor().g;
				_AmbientColor[2] = pLight->GetAmbientColor().b;

				_DiffuesColor[0] = pLight->GetDiffuseColor().r;
				_DiffuesColor[1] = pLight->GetDiffuseColor().g;
				_DiffuesColor[2] = pLight->GetDiffuseColor().b;

				_SpecularColor[0] = pLight->GetSpecularColor().r;
				_SpecularColor[1] = pLight->GetSpecularColor().g;
				_SpecularColor[2] = pLight->GetSpecularColor().b;

				auto pGeneralLight = dynamic_cast<se::GeneralLight*>(pLight);
				auto pPointLight = dynamic_cast<se::PointLight*>(pLight);
				auto pSpotLight = dynamic_cast<se::SpotLight*>(pLight);

				if (pGeneralLight)
				{

					float _Dirrection[3] = { pGeneralLight->GetDirection().x, pGeneralLight->GetDirection().y, pGeneralLight->GetDirection().z };
					ImGui::Text("General light");
					ImGui::DragFloat3("Dirrection", _Dirrection, 0.05f, -1.0f, 1.0f, "%.1f");
					ImGui::ColorEdit3("Ambient", _AmbientColor);
					ImGui::ColorEdit3("Diffuse", _DiffuesColor);
					ImGui::ColorEdit3("Specular", _SpecularColor);
					ImGui::Separator();

					pGeneralLight->SetAmbientColor(_AmbientColor[0], _AmbientColor[1], _AmbientColor[2]);
					pGeneralLight->SetDiffuseColor(_DiffuesColor[0], _DiffuesColor[1], _DiffuesColor[2]);
					pGeneralLight->SetSpecularColor(_SpecularColor[0], _SpecularColor[1], _SpecularColor[2]);
					pGeneralLight->SetDirection(_Dirrection[0], _Dirrection[1], _Dirrection[2]);
				}
				else if (pPointLight)
				{
					float _Position[3] = { pPointLight->GetPosition().x, pPointLight->GetPosition().y, pPointLight->GetPosition().z };
					float _Constant = pPointLight->GetConstant();
					float _Linear = pPointLight->GetLinear();
					float _Qaudratic = pPointLight->GetQaudratic();
					ImGui::Text("Point light");
					ImGui::DragFloat3("Position", _Position, 0.1f, -FLT_MAX, FLT_MAX, "%.1f");
					ImGui::ColorEdit3("Ambient", _AmbientColor);
					ImGui::ColorEdit3("Diffuse", _DiffuesColor);
					ImGui::ColorEdit3("Specular", _SpecularColor);
					ImGui::DragFloat("Constant", &_Constant, 0.01f, 0.0f, FLT_MAX, "%.2f");
					ImGui::DragFloat("Linear", &_Linear, 0.00001f, 0.0f, FLT_MAX, "%.5f");
					ImGui::DragFloat("Qaudratic", &_Qaudratic, 0.00001f, 0.0f, FLT_MAX, "%.5f");
					ImGui::Separator();

					pPointLight->SetAmbientColor(_AmbientColor[0], _AmbientColor[1], _AmbientColor[2]);
					pPointLight->SetDiffuseColor(_DiffuesColor[0], _DiffuesColor[1], _DiffuesColor[2]);
					pPointLight->SetSpecularColor(_SpecularColor[0], _SpecularColor[1], _SpecularColor[2]);
					pPointLight->SetPosition(_Position[0], _Position[1], _Position[2]);

					pPointLight->SetConstant(_Constant);
					pPointLight->SetLinear(_Linear);
					pPointLight->SetQaudratic(_Qaudratic);

				}
				else if (pSpotLight)
				{
					float _Dirrection[3] = { pSpotLight->GetDirection().x, pSpotLight->GetDirection().y, pSpotLight->GetDirection().z };
					float _Position[3] = { pSpotLight->GetPosition().x, pSpotLight->GetPosition().y, pSpotLight->GetPosition().z };
					float _Constant = pSpotLight->GetConstant();
					float _Linear = pSpotLight->GetLinear();
					float _Qaudratic = pSpotLight->GetQaudratic();

					ImGui::Text("Spot light");
					ImGui::DragFloat3("Dirrection", _Dirrection, 0.05f, -1.0f, 1.0f, "%.1f");
					ImGui::DragFloat3("Position", _Position, 0.1f, -FLT_MAX, FLT_MAX, "%.1f");
					ImGui::ColorEdit3("Ambient", _AmbientColor);
					ImGui::ColorEdit3("Diffuse", _DiffuesColor);
					ImGui::ColorEdit3("Specular", _SpecularColor);
					ImGui::DragFloat("Constant", &_Constant, 0.01f, 0.0f, FLT_MAX, "%.2f");
					ImGui::DragFloat("Linear", &_Linear, 0.00001f, 0.0f, FLT_MAX, "%.5f");
					ImGui::DragFloat("Qaudratic", &_Qaudratic, 0.00001f, 0.0f, FLT_MAX, "%.5f");
					ImGui::Separator();

					pSpotLight->SetAmbientColor(_AmbientColor[0], _AmbientColor[1], _AmbientColor[2]);
					pSpotLight->SetDiffuseColor(_DiffuesColor[0], _DiffuesColor[1], _DiffuesColor[2]);
					pSpotLight->SetSpecularColor(_SpecularColor[0], _SpecularColor[1], _SpecularColor[2]);
					pSpotLight->SetPosition(_Position[0], _Position[1], _Position[2]);
					pSpotLight->SetDirection(_Dirrection[0], _Dirrection[1], _Dirrection[2]);

					pSpotLight->SetConstant(_Constant);
					pSpotLight->SetLinear(_Linear);
					pSpotLight->SetQaudratic(_Qaudratic);
				}
			}
		} ImGui::End();

		ImGui::ShowDemoWindow(&show);

		ShowEntities();
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
		
	}
	void ImGuiLayer::ShowEntities()
	{
		if (ImGui::Begin("Entities:"))
		{
			// Left
			static uint32_t selected = 1;
			{
				ImGui::BeginChild("left pane", ImVec2(150, 0), true);
				auto _Entities = GetScene()->GetEntities().view<se::Model3DComponent, se::Transform3DComponent, se::TagComponent>();
				for (auto& _Entity : _Entities)
				{
					if (ImGui::Selectable(std::string(_Entities.get<se::TagComponent>(_Entity).Tag + ": " + std::to_string((uint32_t)_Entity)).c_str(), selected == static_cast<uint32_t>(_Entity)))
					{
						selected = static_cast<uint32_t>(_Entity);
					}

				}
				ImGui::EndChild();
			}
			ImGui::SameLine();

			// Right
			{
				ImGui::BeginGroup();
				ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
				ImGui::Text("ID: %d", selected);
				ImGui::Separator();
				if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Components"))
					{
						ImGui::Text("Transform3D");
						{
							auto& _Tansform = GetScene()->GetEntities().get<se::Transform3DComponent>((entt::entity)selected);
							float _Position[3] = { _Tansform.Transform.GetPosition().x, _Tansform.Transform.GetPosition().y, _Tansform.Transform.GetPosition().z };
							float _Rotation[3] = { _Tansform.Transform.GetRotation().x, _Tansform.Transform.GetRotation().y, _Tansform.Transform.GetRotation().z };
							float _Scale[3] = { _Tansform.Transform.GetScale().x, _Tansform.Transform.GetScale().y, _Tansform.Transform.GetScale().z };


							ImGui::DragFloat3("Position", _Position, 0.01f, -FLT_MAX, FLT_MAX, "%.1f");
							ImGui::Separator();
							ImGui::DragFloat3("Rotation", _Rotation, 0.01f, -FLT_MAX, FLT_MAX, "%.1f");
							ImGui::Separator();
							ImGui::DragFloat3("Scale", _Scale, 0.01f, 0.0f, FLT_MAX, "%.1f");
							ImGui::Separator();
							//ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
							ImGui::EndTabItem();

							_Tansform.Transform.SetPostition(_Position[0], _Position[1], _Position[2]);
							_Tansform.Transform.SetRotation(_Rotation[0], _Rotation[1], _Rotation[2]);
							_Tansform.Transform.SetScale(_Scale[0], _Scale[1], _Scale[2]);
						}

						auto& _Model3DEntities = GetScene()->GetEntities().get<se::Model3DComponent>((entt::entity)selected).Model3D;
						auto _Meshes = _Model3DEntities.get()->GetEntities().view<se::MeshComponent>();

						if (_Meshes.size())
						{
							ImVec2 _AvalibleSpace = ImGui::GetContentRegionAvail();
							ImGui::Text("Textures");
							{
								for (auto& _Mesh : _Meshes)
								{
									auto& _m = _Meshes.get<se::MeshComponent>(_Mesh).Mesh;
									auto _Textures = _m.get()->GetEntities().view<se::TextureComponent>();
									for (auto& _Texture : _Textures)
									{
										ImTextureID tid = reinterpret_cast<void*>(_Textures.get<se::TextureComponent>(_Texture).Texture->GetTextureRenderId());
										ImGui::Image(tid, ImVec2{ 200, 200 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
									}
									
								}
							}
						}


					}
					if (ImGui::BeginTabItem("Asset data"))
					{
						auto& _AssetData = GetScene()->GetEntities().get<se::Model3DComponent>((entt::entity)selected);
						ImGui::TextWrapped("Class name:%s", _AssetData.Model3D.get()->GetAssetClassName().c_str());
						ImGui::Separator();
						ImGui::TextWrapped("Path:%s", _AssetData.Model3D.get()->GetAssetData()->_Path.c_str());
						ImGui::Separator();
						//ImGui::TextWrapped("Type:%s", typeid(_AssetData.Model3D.get()->GetAssetData()->_Type).name());

						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
				ImGui::EndChild();
				if (ImGui::Button("Revert")) {}
				ImGui::SameLine();
				if (ImGui::Button("Save")) {}
				ImGui::EndGroup();
			}
		}
		ImGui::End();
	}

	void ImGuiLayer::ShowVewPort()
	{

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
	void ImGuiLayer::ShowAssetList()
	{
		if (ImGui::Begin("Assets:"))
		{
			// Left
			static uint32_t selected = 1;

			auto _Entities = GetScene()->GetEntities().view<se::Model3DComponent, se::Transform3DComponent, se::TagComponent>();

			auto& _Asset = se::AssetManager::GetAssetDataList();
			if (ImGui::TreeNode(_Asset._Name.c_str()))
			{
				//ImGui::Text(_Asset._Name.c_str());
					
				if (_Asset._Dependency.size() > 0)
				{
					
					for (auto& elem : _Asset._Dependency)
					{
						if (ImGui::TreeNode(elem._Name.c_str()))
						{
							ImGui::Text(elem._Name.c_str());
							ImGui::TreePop();
							ImGui::Separator();
						}
					}
				}	

				ImGui::TreePop();
				ImGui::Separator();
			}
			
			
		} ImGui::End();
	}
}