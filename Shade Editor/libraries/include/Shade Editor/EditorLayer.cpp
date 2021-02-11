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

				if (m_SelectedEntity)
				{
					if (m_SelectedEntity.HasComponent<se::Transform3DComponent>())
					{
						auto& transform = m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform;
						auto modelMatrix = transform.GetModelMatrix();
						if (ShowGuizmo(modelMatrix, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()))
						{
							glm::vec3 position, rotation, scale;
							ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(modelMatrix), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));

							transform.SetPostition(position);
							transform.SetRotation(glm::radians(rotation));
							transform.SetScale(scale);
						}
					}
				}

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

		if (ImGui::TreeNode("Entities"))
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

	if (ImGui::Begin("Environment"))
	{
		GetScene()->GetEntities().each([&](auto entityID)
			{
				se::Entity entity{ entityID , GetScene() };
				if (entity.HasComponent<se::EnvironmentComponent>())
				{
					DrawEnvironmentEntity(entity);
				}

			});

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
	/*if (entity.HasComponent<se::TagComponent>())
	{
		if (ImGui::TreeNode("Name"))
		{
			//ImGui::Separator();
			auto& tag = entity.GetComponent<se::TagComponent>().Tag;
			static char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			std::strncpy(buffer, tag.c_str(), sizeof(buffer));
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
				tag = std::string(buffer);

			ImGui::TreePop();
		}
	}*/

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

void EditorLayer::DrawEnvironmentEntity(const se::Entity& entity)
{
	if (entity) // is not 0
	{

		auto& environment = entity.GetComponent<se::EnvironmentComponent>().Environment;
		switch (environment->Type)
		{
		case se::Environment::EnvironmentType::Environment:
			break;
		case se::Environment::EnvironmentType::GeneralLight:
		{

			auto pLight = static_cast<se::GeneralLight*>(environment.get());
			break;
		}
		case se::Environment::EnvironmentType::PointLight:
		{
			std::string name;
			entity.HasComponent<se::TagComponent>() ? name = entity.GetComponent<se::TagComponent>().Tag + "##" + entity : name = std::string("##") + entity;

			if (ImGui::TreeNode(name.c_str()))
			{
				m_SelectedEntity = se::Entity();

				auto pLight = static_cast<se::PointLight*>(environment.get());
				DrawVec3("Position", pLight->GetPosition());
				DrawColor3("Ambient", pLight->GetAmbientColor());
				DrawColor3("Diffuse", pLight->GetDiffuseColor());
				DrawColor3("Specular", pLight->GetSpecularColor());

				glm::mat4 position = glm::translate(pLight->GetPosition());

				if (ShowGuizmo(position, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()))
				{
					glm::vec3 pos, rot, sc;
					ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(position), glm::value_ptr(pos), glm::value_ptr(rot), glm::value_ptr(sc));
					pLight->SetPosition(pos);
				}

				ImGui::TreePop();
			}
			break;
		}
		case se::Environment::EnvironmentType::SpotLight:
		{
			auto pLight = static_cast<se::SpotLight*>(environment.get());
			break;
		}
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
									se::Entity entity{ entityID , model3D.get() };
									if (ImGui::TreeNode(std::string("##mesh" + entity).c_str(), "Mesh: %s", entity.GetComponent<se::MeshComponent>().Mesh->GetAssetData()._Name.c_str()))
									{
										if (ImGui::TreeNode(std::string("##material" + entity).c_str(), "Material"))
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

							ImGui::TreePop();
						}
					}

					ImGui::EndTabItem();
				}


			} ImGui::EndTabBar();
		}

	} ImGui::End();
}

bool EditorLayer::ShowGuizmo(glm::mat4& transform, const float& x, const float& y, const float& width, const float& height)
{
	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

	auto cameraView = GetScene()->GetActiveCamera()->GetView();
	auto cameraProjection = GetScene()->GetActiveCamera()->GetProjection();

	ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), m_GuizmoOperation, ImGuizmo::LOCAL, glm::value_ptr(transform));

	if (ImGuizmo::IsUsing())
		return true;
	else 
		return false;
}
