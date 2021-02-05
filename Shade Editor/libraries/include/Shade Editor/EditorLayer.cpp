#include "stdafx.h"
#include "EditorLayer.h"

EditorLayer::EditorLayer(const std::string& name, se::Scene* scene) : se::ImGuiLayer(name, scene)
{

}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::OnCreate()
{
	se::EventManager::RegLayerEventCallback(se::EventType::SDL_KEYDOWN, GetScene(),this,
		[&](se::Event const& event) {
		
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				switch (m_GuizmoOperation)
				{
				case ImGuizmo::OPERATION::TRANSLATE:
					m_GuizmoOperation = ImGuizmo::OPERATION::ROTATE;
					break;
				case ImGuizmo::OPERATION::ROTATE:
					m_GuizmoOperation = ImGuizmo::OPERATION::SCALE;
					break;
				case ImGuizmo::OPERATION::SCALE:
					m_GuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
					break;
				}
				
			}

			return false;
		});
}

void EditorLayer::OnInit()
{
	
}

void EditorLayer::OnUpdate(const se::Timer& deltaTime)
{
	
}

void EditorLayer::OnRender()
{
	static bool show = true;

	if (ImGui::Begin("DockSpace", (bool*)(nullptr), m_WindowFlags))
	{
		ShowMenu();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("DockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), m_DockSpaceFlags);
		}


	} ImGui::End(); // Begin("DockSpace")*/


	
	ShowAssetDataList();
	ShowSceneEntities();
	ShowMainScene();
	ShowLightningSource();
}

void EditorLayer::OnDelete()
{
}

void EditorLayer::ShowMainScene()
{
	if (ImGui::Begin("Scene"))
	{
		auto frameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");
		if ( frameBuffer != nullptr)
		{
			auto viewPortEntitis = GetScene()->GetEntities().view<glm::fvec2, se::TagComponent>();

			for (auto& viewPort : viewPortEntitis)
			{
				if (viewPortEntitis.get<se::TagComponent>(viewPort).Tag == "MainSceneDocViewPort")
				{
					auto& viewPortSize = viewPortEntitis.get<glm::fvec2>(viewPort);
					if (viewPortSize.x != ImGui::GetContentRegionAvail().x
						|| viewPortSize.y != ImGui::GetContentRegionAvail().y)
					{
						viewPortSize.x = ImGui::GetContentRegionAvail().x;
						viewPortSize.y = ImGui::GetContentRegionAvail().y;

						//Create window resize event and grab it in MainLayer
						se::Event _Event;
						_Event.type = SDL_WINDOWEVENT;
						_Event.window.event = SDL_WINDOWEVENT_RESIZED;
						se::EventManager::PusEvent(_Event);
					}
				}
				

				ImTextureID tid = reinterpret_cast<void*>(frameBuffer->GetTextureAttachment());
				ImGui::Image(tid, ImVec2{ ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

				// ImGuizmo
				{
					ImGuizmo::SetOrthographic(false);
					ImGuizmo::SetDrawlist();
					ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

					auto& transformComponent = GetScene()->GetEntities().get<se::Transform3DComponent>((entt::entity)m_SelectedEntityID).Transform;
					auto modelMatrix = transformComponent.GetModelMatrix();
					auto cameraView = GetScene()->GetActiveCamera()->GetView();
					auto cameraProjection = GetScene()->GetActiveCamera()->GetProjection();

				
					ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), m_GuizmoOperation, ImGuizmo::LOCAL, glm::value_ptr(modelMatrix));

					{
						
						//static glm::mat4 gridMatrix(1.0f);
						//ImGuizmo::DrawGrid(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), glm::value_ptr(gridMatrix), 100.f);
					
					}
					

					glm::vec3 position, rotation, scale;
					ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(modelMatrix), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));

					ShowFpsOverlay(ImGui::GetWindowViewport(), ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);

					if (ImGuizmo::IsUsing())
					{
						transformComponent.SetPostition(position);
						transformComponent.SetRotation(glm::radians(rotation));
						transformComponent.SetScale(scale);
					}

				}
			}
		}


	} ImGui::End(); // ImGui::Begin("Scene")
}

void EditorLayer::ShowSceneEntities()
{
	ShowDemoWindow();

	if (ImGui::Begin("Entities"))
	{
		auto _Entities = GetScene()->GetEntities().view<se::Model3DComponent, se::Transform3DComponent, se::TagComponent>();

		for (auto& _Entity : _Entities)
		{
			if (ImGui::Selectable(std::string(_Entities.get<se::TagComponent>(_Entity).Tag + ": " + std::to_string((uint32_t)_Entity)).c_str(), m_SelectedEntityID == static_cast<uint32_t>(_Entity)))
				m_SelectedEntityID = (uint32_t)_Entity;

		}


	} ImGui::End();

	if (ImGui::Begin("Inspector"))
	{
		if (ImGui::BeginTabBar("InspectorTabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Components"))
			{
			
				ImGui::Text("TagComponent"); ImGui::Separator();
				{
					auto& tag = GetScene()->GetEntities().get<se::TagComponent>((entt::entity)m_SelectedEntityID).Tag;
					static char buffer[50] = " ";
					for (auto i = 0; i < tag.size(); i++)
						buffer[i] = tag[i];

					if (ImGui::InputText("##TagComponent", buffer, 50))
					{
						tag = buffer;
					}
						
					ImGui::Separator();

				}
				ImGui::Text("Transform3D"); ImGui::Separator();
				{
					auto& tansform = GetScene()->GetEntities().get<se::Transform3DComponent>((entt::entity)m_SelectedEntityID).Transform;
					{
						ImGui::Text("Position");
						ImGui::PushItemWidth(100);
						ImGui::DragFloat("X##P", &tansform.GetPositionRef().x, 0.01f, -FLT_MAX, FLT_MAX, "%.2f"); ImGui::SameLine();
						ImGui::PushItemWidth(100);
						ImGui::DragFloat("Y##P", &tansform.GetPositionRef().y, 0.01f, -FLT_MAX, FLT_MAX, "%.2f"); ImGui::SameLine();
						ImGui::PushItemWidth(100);
						ImGui::DragFloat("Z##P", &tansform.GetPositionRef().z, 0.01f, -FLT_MAX, FLT_MAX, "%.2f");
					}
					{
						ImGui::Text("Rotation");
						ImGui::PushItemWidth(100);
						ImGui::DragFloat("X##R", &tansform.GetRotationRef().x, 0.01f, -FLT_MAX, FLT_MAX, "%.2f"); ImGui::SameLine();
						ImGui::PushItemWidth(100);
						ImGui::DragFloat("Y##R", &tansform.GetRotationRef().y, 0.01f, -FLT_MAX, FLT_MAX, "%.2f"); ImGui::SameLine();
						ImGui::PushItemWidth(100);
						ImGui::DragFloat("Z##R", &tansform.GetRotationRef().z, 0.01f, -FLT_MAX, FLT_MAX, "%.2f");
					}
					{
						ImGui::Text("Scale");
						ImGui::PushItemWidth(100);
						ImGui::DragFloat("X##S", &tansform.GetScaleRef().x, 0.005f, 0.0f, FLT_MAX, "%.3f"); ImGui::SameLine();
						ImGui::PushItemWidth(100);
						ImGui::DragFloat("Y##S", &tansform.GetScaleRef().y, 0.005f, 0.0f, FLT_MAX, "%.3f"); ImGui::SameLine();
						ImGui::PushItemWidth(100);
						ImGui::DragFloat("Z##S", &tansform.GetScaleRef().z, 0.005f, 0.0f, FLT_MAX, "%.3f");
					}
				}
				ImGui::EndTabItem();
			}

			auto meshes = GetScene()->GetEntities().get<se::Model3DComponent>((entt::entity)m_SelectedEntityID).Model3D->GetEntities().view<se::MeshComponent>();

			if (meshes.size())
			{
				if (ImGui::BeginTabItem("Textures"))
				{
					for (auto& mesh : meshes)
					{
						auto textures = meshes.get<se::MeshComponent>(mesh).Mesh->GetEntities().view<se::TextureComponent>();

						for (auto& texture : textures)
						{
							ImVec2 _AvalibleSpace = ImGui::GetContentRegionAvail();

							ImTextureID tid = reinterpret_cast<void*>(textures.get<se::TextureComponent>(texture).Texture->GetTextureRenderId());
							ImGui::Image(tid, ImVec2{ 200, 200 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
							if (_AvalibleSpace.x >= 200)
								ImGui::SameLine();
						}

					}
					ImGui::EndTabItem();
				}
			}

		} ImGui::EndTabBar();

	} ImGui::End();
}

void EditorLayer::ShowAssetDataList()
{
	if (ImGui::Begin("Assets"))
	{
		// Left
		static uint32_t selected = 1;

		auto _Entities = GetScene()->GetEntities().view<se::Model3DComponent, se::Transform3DComponent, se::TagComponent>();

		auto& _Asset = se::AssetManager::GetAssetDataList();
		if (ImGui::TreeNode(_Asset._Name.c_str()))
		{
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


	} ImGui::End(); // ImGui::Begin("Assets")
}

void EditorLayer::ShowMenu()
{
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


	} ImGui::EndMenuBar();
}

void EditorLayer::ShowLightningSource()
{
	auto lights = GetScene()->GetEntities().view<se::EnvironmentComponent>();
	if (ImGui::Begin("Lightning sources"))
	{
		for (auto& light : lights)
		{
			
			auto pGeneralLight = dynamic_cast<se::GeneralLight*>(lights.get<se::EnvironmentComponent>(light).Environment.get());
			auto pPointLight = dynamic_cast<se::PointLight*>(lights.get<se::EnvironmentComponent>(light).Environment.get());
			auto pSpotLight = dynamic_cast<se::SpotLight*>(lights.get<se::EnvironmentComponent>(light).Environment.get());

			if (pGeneralLight)
			{
				ImGui::Text("General light");
				ImGui::DragFloat3("Dirrection##G", glm::value_ptr(pGeneralLight->GetDirectionRef()), 0.05f, -1.0f, 1.0f, "%.2f");
				ImGui::ColorEdit3("Ambient##G", glm::value_ptr(pGeneralLight->GetAmbientColorRef()));
				ImGui::ColorEdit3("Diffuse##G", glm::value_ptr(pGeneralLight->GetDiffuseColorRef()));
				ImGui::ColorEdit3("Specular##G", glm::value_ptr(pGeneralLight->GetSpecularColorRef()));
				ImGui::Separator();
			}
			else if (pPointLight)
			{
				ImGui::Text("Point light");
				ImGui::DragFloat3("Position##P", glm::value_ptr(pPointLight->GetPositionRef()), 0.05f, -FLT_MAX, FLT_MAX, "%.2f");
				ImGui::ColorEdit3("Ambient##P", glm::value_ptr(pPointLight->GetAmbientColorRef()));
				ImGui::ColorEdit3("Diffuse##P", glm::value_ptr(pPointLight->GetDiffuseColorRef()));
				ImGui::ColorEdit3("Specular##P", glm::value_ptr(pPointLight->GetSpecularColorRef()));
				ImGui::Separator();
			}
			else if (pSpotLight)
			{
				ImGui::Text("Point light");
				ImGui::DragFloat3("Position##P", glm::value_ptr(pPointLight->GetPositionRef()), 0.05f, -FLT_MAX, FLT_MAX, "%.2f");
				ImGui::ColorEdit3("Ambient##P", glm::value_ptr(pPointLight->GetAmbientColorRef()));
				ImGui::ColorEdit3("Diffuse##P", glm::value_ptr(pPointLight->GetDiffuseColorRef()));
				ImGui::ColorEdit3("Specular##P", glm::value_ptr(pPointLight->GetSpecularColorRef()));
				ImGui::Separator();
			}
		}
	} ImGui::End();
}

void EditorLayer::ShowFpsOverlay(ImGuiViewport* viewport, const float& x, const float& y)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoDecoration | 
		ImGuiWindowFlags_NoDocking | 
		ImGuiWindowFlags_AlwaysAutoResize | 
		ImGuiWindowFlags_NoSavedSettings | 
		ImGuiWindowFlags_NoFocusOnAppearing | 
		ImGuiWindowFlags_NoNav;

	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	ImGui::SetNextWindowPos(ImVec2{ ImGui::GetWindowPos().x + 12, ImGui::GetWindowPos().y + 32 }, ImGuiCond_Always);
	if (ImGui::Begin("Example: Simple overlay", nullptr, window_flags))
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::Separator();
	}
	ImGui::End();
}
