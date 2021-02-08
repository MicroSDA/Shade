#ifdef _MSVC_LANG
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "stdafx.h"
#include "EditorLayer.h"
#include <cstring>



EditorLayer::EditorLayer(const std::string& name, se::Scene* scene) : se::ImGuiLayer(name, scene)
{

}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::OnCreate()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("./resources/fonts/imgui/Ruda-Black.ttf", 17.0f);


	se::EventManager::RegLayerEventCallback(se::EventType::SDL_KEYDOWN, GetScene(), this,
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
	ShowEntities();
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
		if (frameBuffer != nullptr)
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
				ShowGuizmo();
				ShowFpsOverlay(ImGui::GetWindowViewport(), ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
			}
		}


	} ImGui::End(); // ImGui::Begin("Scene")
}

void EditorLayer::ShowEntities()
{
	if (ImGui::Begin("Entities"))
	{
		static char buffer[256];
		memset(buffer, 0, sizeof(buffer));

		ImGui::NewLine();
		ImGui::Text("Search:"); ImGui::SameLine();
		ImGui::InputText("##EntitiesSearch", buffer, sizeof(buffer));
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		if (ImGui::TreeNode("Environment"))
		{
			GetScene()->GetEntities().each([&](auto entityID)
				{
					se::Entity entity{ entityID , GetScene() };
					if (entity.HasComponent<se::EnvironmentComponent>())
						DrawEntity(entity);
				});
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Others"))
		{
			GetScene()->GetEntities().each([&](auto entityID)
				{
					se::Entity entity{ entityID , GetScene() };
					if (!entity.HasComponent<se::EnvironmentComponent>())
						DrawEntity(entity);
				});
			ImGui::TreePop();
		}
		
	} ImGui::End();

	ShowEntitiesInspector();
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
		ImGui::Text("Application average %.1f ms/frame (%.0f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}
	ImGui::End();
}

void EditorLayer::DrawEntity(const se::Entity& entity)
{
	if (entity) // is not 0
	{
		if (entity.HasComponent<se::TagComponent>())
		{
			auto& tag = entity.GetComponent<se::TagComponent>().Tag;
			ImGui::Dummy(ImVec2()); ImGui::SameLine(25.0f);
			if (ImGui::Selectable(std::string(tag + "##" + entity).c_str(), m_SelectedEntity == entity))
				m_SelectedEntity = entity;
		}
	}

}

void EditorLayer::ShowEntitiesInspector()
{
	ShowDemoWindow();

	if (ImGui::Begin("Inspector"))
	{
		if (m_SelectedEntity)
		{
			if (ImGui::BeginTabBar("InspectorTabs", ImGuiTabBarFlags_None))
			{
				if (ImGui::BeginTabItem("Components"))
				{
					if (ImGui::TreeNode("Name"))
					{
						//ImGui::Separator();
						auto& tag = m_SelectedEntity.GetComponent<se::TagComponent>().Tag;
						static char buffer[256];
						memset(buffer, 0, sizeof(buffer));
						std::strncpy(buffer, tag.c_str(), sizeof(buffer));
						if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
							tag = std::string(buffer);

						ImGui::TreePop();
						//ImGui::Separator();
					}

					if (m_SelectedEntity.HasComponent<se::Transform3DComponent>())
					{
						if (ImGui::TreeNode("Transform3D"))
						{
							auto& transform = m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform;
							{
								DrawVec3("Position", transform.GetPositionRef(), 0.0f);
								DrawVec3("Rotation", transform.GetRotationRef(), 0.0f);
								DrawVec3("Scale", transform.GetScaleRef(), 1.0f);
							}
							
							ImGui::TreePop();
						}
					}

					if (m_SelectedEntity.HasComponent<se::Model3DComponent>())
					{
						if (ImGui::TreeNode("Model3D"))
						{
							auto& model3D = m_SelectedEntity.GetComponent<se::Model3DComponent>().Model3D;

							model3D->GetEntities().each([&](auto entityID) 
								{
									se::Entity entity { entityID , model3D.get() };
									if (ImGui::TreeNode(std::string("##mesh" + entity).c_str(), "Mesh: %s", entity.GetComponent<se::MeshComponent>().Mesh->GetAssetData()->_Name.c_str()))
									{
										if (ImGui::TreeNode(std::string("##material"+ entity).c_str(), "Material"))
										{
											auto& material = entity.GetComponent<se::MaterialComponent>().Material;

											DrawColor3("Ambient", material.GetAmbientColor(), 150.0f);
											DrawColor3("Diffuse", material.GetDiffuseColor(), 150.0f);
											DrawColor3("Specular", material.GetSpecularColor(), 150.0f);
											DrawDragFloat("Shinness", material.GetShininess(), 0.0, 150.0f);
											DrawDragFloat("Shinness strength", material.GetShininessStrength(), 0.0, 150.0f);
											ImGui::TreePop();
										}

										ImGui::TreePop();
									}

									
								});
							

							/*for (auto& mesh : model3D->GetEntities().view<se::MeshComponent, se::MaterialComponent>())
							{
								if (ImGui::TreeNode(model3D->GetEntities().get<se::MeshComponent>(mesh).Mesh->GetAssetData()->_Name.c_str()))
								{
									auto& material = model3D->GetEntities().get<se::MaterialComponent>(mesh).Material;
					
									DrawColor3("Ambient",              material.GetAmbientColor(), 150.0f);
									DrawColor3("Diffuse",              material.GetDiffuseColor(), 150.0f);
									DrawColor3("Specular",             material.GetSpecularColor(), 150.0f);
									DrawDragFloat("Shinness",          material.GetShininess(), 0.0, 150.0f);
									DrawDragFloat("Shinness strength", material.GetShininessStrength(),0.0, 150.0f);
									ImGui::TreePop();
								}
								
							}*/

							//ImGui::Text("Material");
							ImGui::TreePop();
						}
					}

					ImGui::EndTabItem();
				}


			} ImGui::EndTabBar();
		}

	} ImGui::End();
}

void EditorLayer::ShowGuizmo()
{
	if (m_SelectedEntity)
	{
		if (m_SelectedEntity.HasComponent<se::Transform3DComponent>())
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

			auto& transform = m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform;
			auto modelMatrix = transform.GetModelMatrix();
			auto cameraView = GetScene()->GetActiveCamera()->GetView();
			auto cameraProjection = GetScene()->GetActiveCamera()->GetProjection();

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), m_GuizmoOperation, ImGuizmo::LOCAL, glm::value_ptr(modelMatrix));

			glm::vec3 position, rotation, scale;
			ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(modelMatrix), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));

			if (ImGuizmo::IsUsing())
			{
				transform.SetPostition(position);
				transform.SetRotation(glm::radians(rotation));
				transform.SetScale(scale);
			}

		}
	}
}
