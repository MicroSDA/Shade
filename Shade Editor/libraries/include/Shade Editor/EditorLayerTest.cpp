#ifdef _MSVC_LANG
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "stdafx.h"
#include "EditorLayerTest.h"
#include "Shade/Core/Util/FileDialog.h"
#include "Editor.h"

EditorLayerTest::EditorLayerTest(const std::string& name, se::Scene* scene) : se::ImGuiLayer(name, scene)
{
}

EditorLayerTest::~EditorLayerTest()
{
}

void EditorLayerTest::OnCreate()
{
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

void EditorLayerTest::OnInit()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("./resources/fonts/imgui/Ruda-Black.ttf", 17.0f);
}

void EditorLayerTest::OnUpdate(const se::Timer& deltaTime)
{
}

void EditorLayerTest::OnRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	if (ImGui::Begin("DockSpace", (bool*)(nullptr), m_WindowFlags))
	{
		ImGui::PopStyleVar();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("DockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), m_DockSpaceFlags);
		}

		this->ShowMainMenu(isMainMenuShow);
		this->ShowEntitiesList(isEntitiesListShow);
		this->ShowInspector(isInspectorShow);
		this->ShowScene(isSceneShow);

	} ImGui::End(); // Begin("DockSpace")*/

}

void EditorLayerTest::OnDelete()
{
}

void EditorLayerTest::ShowMainMenu(const bool& show)
{
	if (show)
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New")) {}

				if (ImGui::MenuItem("Open")) 
				{ 
					std::cout << se::FileDialog::OpenFile("") << std::endl;
				}

				if (ImGui::MenuItem("Save")) {}

				if (ImGui::MenuItem("Import"))
				{
					std::string path = se::FileDialog::OpenFile("Model3D\0");
					if(!path.empty())
						Editor::Import(Editor::ImportType::Model3D, path);
				}

				ImGui::Separator();
				if (ImGui::MenuItem("Exit"))  se::Application::GetApplication().Quit();
				ImGui::EndMenu();
			}



		} ImGui::EndMenuBar();
	}
}

void EditorLayerTest::ShowEntitiesList(const bool& show)
{
	if (show)
	{
		ImGui::Begin("Entities");
		{
			GetScene()->GetEntities().each([&](auto entityID)
				{
					se::Entity entity{ entityID , GetScene() };
					ProcessEntities(entity);

				});
		}
		ImGui::End();
	}
}

void EditorLayerTest::ProcessEntities(se::Entity& entity)
{
	if (entity.HasComponent<se::TagComponent>())
	{
		auto& tag = entity.GetComponent<se::TagComponent>().Tag;
		//ImGui::Dummy(ImVec2()); ImGui::SameLine(25.0f);
		if (ImGui::Selectable(std::string(tag + "##" + entity).c_str(), m_SelectedEntity == entity))
			m_SelectedEntity = entity;
	}
}

void EditorLayerTest::ShowInspector(const bool& show)
{
	if (show)
	{
		ImGui::Begin("Inspector");
		{
			if (m_SelectedEntity)
			{
				if (ImGui::BeginTabBar("InspectorTabs", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Components"))
					{
						ShowTagComponent(m_SelectedEntity, isTagComponentShow);
						ShowTransform3DComponent(m_SelectedEntity, isTransform3DComponentShow);
						ShowModel3DComponent(m_SelectedEntity, isModel3DComponentShow);
						ShowEnvironmentComponent(m_SelectedEntity, isEnvironmentComponentShow);

						ImGui::EndTabItem();
					}

				} ImGui::EndTabBar();
			}

		}
		ImGui::End();
	}
}

void EditorLayerTest::ShowScene(const bool& show)
{
	if (show)
	{
		ImGui::Begin("Scene");
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
							auto transform = m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform.GetModelMatrix();

							if (this->ShowImGuizmo(transform, true, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y))
							{
								glm::vec3 position, rotation, scale;
								ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));

								m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform.SetPostition(position);
								m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform.SetRotation(glm::radians(rotation));
								m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform.SetScale(scale);
							}
						}
						else if (m_SelectedEntity.HasComponent<se::EnvironmentComponent>())
						{
							auto environment = m_SelectedEntity.GetComponent<se::EnvironmentComponent>().Environment.get();
							switch (environment->Type)
							{
							case se::Environment::EnvironmentType::Environment:
								break;
							case se::Environment::EnvironmentType::GeneralLight:
							{
								auto pLight = static_cast<se::GeneralLight*>(environment);
								glm::mat4 transform = glm::toMat4(glm::quat((pLight->GetDirection())));

								if (this->ShowImGuizmo(transform, true, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y))
								{
									glm::vec3 position, rotation, scale;
									ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));
									pLight->SetDirection(glm::radians(rotation)); // TODO: Normalize
								}
								break;
							}
							case se::Environment::EnvironmentType::PointLight:
							{
								auto pLight = static_cast<se::PointLight*>(environment);

								glm::mat4 transform = glm::translate(pLight->GetPosition());
								if (this->ShowImGuizmo(transform, true, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y))
								{
									glm::vec3 position, rotation, scale;
									ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));
									pLight->SetPosition(position);
								}

								break;
							}
							case se::Environment::EnvironmentType::SpotLight:
								auto pLight = static_cast<se::SpotLight*>(environment);

								glm::mat4 translate = glm::translate(pLight->GetPosition());
								glm::mat4 rotate    = glm::toMat4(glm::quat(pLight->GetDirection()));
								glm::mat4 transform = translate * rotate;
								if (this->ShowImGuizmo(transform, true, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y))
								{
									glm::vec3 position, rotation, scale;
									ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));
									pLight->SetPosition(position);
									pLight->SetDirection(glm::radians(rotation));
								}
								break;
							}
						}

					}

				}
			}

			ShowFpsOverlay(ImGui::GetWindowViewport(), isFpsShow, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);

		
		}
		ImGui::End(); // ImGui::Begin("Scene")
		
	}
}

void EditorLayerTest::ShowTagComponent(se::Entity& entity, const bool& show)
{
	if (show)
	{
		if (m_SelectedEntity.HasComponent<se::TagComponent>())
		{
			if (ImGui::TreeNode("Name"))
			{
				static char buffer[256]; memset(buffer, 0, sizeof(buffer));
				auto& tag = m_SelectedEntity.GetComponent<se::TagComponent>().Tag;
				std::strncpy(buffer, tag.c_str(), sizeof(buffer));

				if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
					tag = std::string(buffer);

				ImGui::TreePop();
			}
		}
	}
}

void EditorLayerTest::ShowTransform3DComponent(se::Entity& entity, const bool& show)
{
	if (show)
	{
		if (m_SelectedEntity.HasComponent<se::Transform3DComponent>())
		{
			if (ImGui::TreeNode("Transform3D"))
			{
				auto& transform = m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform;
				{
					DrawVec3("Position", transform.GetPositionRef(), -FLT_MAX, FLT_MAX, 0.0, 100.0f, 400.0f);
					DrawVec3("Rotation", transform.GetRotationRef(), -FLT_MAX, FLT_MAX, 0.0, 100.0f, 400.0f);
					DrawVec3("Scale", transform.GetScaleRef(), 0.0f, FLT_MAX, 1.0f, 100.0f, 400.0f);
				}

				ImGui::TreePop();
			}
		}
	}
}

void EditorLayerTest::ShowModel3DComponent(se::Entity& entity, const bool& show)
{
	if (show)
	{
		if (entity.HasComponent<se::Model3DComponent>())
		{
			if (ImGui::TreeNode("Model3D"))
			{
				auto& model3D = m_SelectedEntity.GetComponent<se::Model3DComponent>().Model3D;

				model3D->GetEntities().each([&](auto entityID)
					{
						se::Entity entity{ entityID , model3D.get() };
						ShowMeshComponent(entity, isModel3DComponentShow);
					});

				ImGui::TreePop();
			}
		}
	}
}

void EditorLayerTest::ShowMeshComponent(se::Entity& entity, const bool& show)
{
	if (show)
	{
		if (entity.HasComponent<se::MeshComponent>())
		{
			std::string name = "Mesh: " + entity.GetComponent<se::MeshComponent>().Mesh->GetAssetData()._Name;

			if (ImGui::TreeNode(name.c_str()))
			{
				this->ShowMaterialComponent(entity, entity.GetComponent<se::MeshComponent>(), isMaterialComponentShow);
				ImGui::TreePop();
			}
		}
	}
	
}

void EditorLayerTest::ShowMaterialComponent(se::Entity& entity, se::MeshComponent& mesh, const bool& show)
{
	if (show)
	{
		if (entity.HasComponent<se::MaterialComponent>())
		{
			uint32_t id = entity;
			if (ImGui::TreeNode(std::string("##material" + std::to_string(id)).c_str(), "Material"))
			{
				auto& material = entity.GetComponent<se::MaterialComponent>().Material;
				DrawColor3("Ambient", material.GetAmbientColor(), 150.0f, 400.0f);
				DrawColor3("Diffuse", material.GetDiffuseColor(), 150.0f, 400.0f);
				DrawColor3("Specular", material.GetSpecularColor(), 150.0f, 400.0f);
				DrawDragFloat("Shinness", material.GetShininess(), 0.0, 150.0f, 400.0f);
				DrawDragFloat("Shinness strength", material.GetShininessStrength(), 0.0, 150.0f, 400.0f);
				mesh.Mesh->GetEntities().each([&](auto entityID)
					{
						se::Entity entity{ entityID , mesh.Mesh.get() };
						ShowTextureComponent(entity, isTextureComponentShow);
					});
				ImGui::TreePop();
			}
		}
	}
}

void EditorLayerTest::ShowTextureComponent(se::Entity& entity, const bool& show)
{
	if (show)
	{
		if (entity.HasComponent<se::TextureComponent>())
		{
			const float width = 100.0f, height = 100.0f;
			auto texture = entity.GetComponent<se::TextureComponent>().Texture;
			ImTextureID tid = reinterpret_cast<void*>(texture->GetTextureRenderId());
			uint32_t id = entity;
			if (ImGui::TreeNode(std::string("##" + std::to_string(id)).c_str(), "Texture: %s", texture->GetAssetData()._Name.c_str()))
			{
				switch (texture->GetAssetData()._SubType)
				{
				case se::AssetDataSubType::Diffuse:
					ImGui::Text("Type: Diffuse");
					break;
				case se::AssetDataSubType::Specular:
					ImGui::Text("Type: Specular");
					break;
				case se::AssetDataSubType::NormalMap:
					ImGui::Text("Type: NormalMap");
					break;
				}
				
				ImGui::Image(tid, ImVec2{ width, height }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
				ImGui::TreePop();
			}
		}
	}
}

void EditorLayerTest::ShowEnvironmentComponent(se::Entity& entity, const bool& show)
{
	if (show)
	{
		if (m_SelectedEntity.HasComponent<se::EnvironmentComponent>())
		{
			auto environment = m_SelectedEntity.GetComponent<se::EnvironmentComponent>().Environment.get();
			switch (environment->Type)
			{
			case se::Environment::EnvironmentType::Environment:
				break;
			case se::Environment::EnvironmentType::GeneralLight:
			{
				m_GuizmoOperation = ImGuizmo::OPERATION::ROTATE;
				auto pLight = static_cast<se::GeneralLight*>(environment);
				this->DrawVec3("Direction", pLight->GetDirection(), -1.0f, 1.0f, 0.0f, 100.0f, 450.0f);
				this->DrawColor3("Ambient", pLight->GetAmbientColor(), 100, 400.0f);
				this->DrawColor3("Diffuse", pLight->GetDiffuseColor(), 100, 400.0f);
				this->DrawColor3("Specular", pLight->GetSpecularColor(), 100, 400.0f);
				break;
			}
			case se::Environment::EnvironmentType::PointLight:
			{
				m_GuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
				auto pLight = static_cast<se::PointLight*>(environment);
				this->DrawVec3("Position", pLight->GetPosition(), -FLT_MAX, FLT_MAX, 0.0f, 100.0f, 450.0f);
				this->DrawColor3("Ambient", pLight->GetAmbientColor(), 100.0f, 400.0f);
				this->DrawColor3("Diffuse", pLight->GetDiffuseColor(), 100.0f, 400.0f);
				this->DrawColor3("Specular", pLight->GetSpecularColor(), 100.0f, 400.0f);
				this->DrawDragFloat("Constant", pLight->GetConstant(), 1.0f, 100.0f, 400.0f);
				this->DrawDragFloat("Linear", pLight->GetLinear(), 0.7f, 100.0f, 400.0f);
				this->DrawDragFloat("Qaudratic", pLight->GetQaudratic(), 1.8f, 100.0f, 400.0f);
				break; 
			}
			case se::Environment::EnvironmentType::SpotLight:
				auto pLight = static_cast<se::SpotLight*>(environment);
				this->DrawVec3("Position", pLight->GetPosition(), -FLT_MAX, FLT_MAX, 0.0f, 100.0f, 450.0f);
				this->DrawVec3("Dirrection", pLight->GetDirection(), -1.0, 1.0, 0.0f, 100.0f, 450.0f);
				this->DrawColor3("Ambient", pLight->GetAmbientColor(), 100.0f, 400.0f);
				this->DrawColor3("Diffuse", pLight->GetDiffuseColor(), 100.0f, 400.0f);
				this->DrawColor3("Specular", pLight->GetSpecularColor(), 100.0f, 400.0f);
				this->DrawDragFloat("Min angle", pLight->GetMinAngle(), 0.5f, 100.0f, 400.0f);
				this->DrawDragFloat("Max angle", pLight->GetMaxAngle(), 0.7f, 100.0f, 400.0f);
				this->DrawDragFloat("Constant", pLight->GetConstant(), 1.0f, 100.0f, 400.0f);
				this->DrawDragFloat("Linear", pLight->GetLinear(), 0.7f, 100.0f, 400.0f);
				this->DrawDragFloat("Qaudratic", pLight->GetQaudratic(), 1.8f, 100.0f, 400.0f);
				break;
			}
		}
	}
}

bool EditorLayerTest::ShowImGuizmo(glm::mat4& transform, const bool& show, const float& x, const float& y, const float& w, const float& h)
{
	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(x, y, w, h);

	auto cameraView = GetScene()->GetActiveCamera()->GetView();
	auto cameraProjection = GetScene()->GetActiveCamera()->GetProjection();

	ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), m_GuizmoOperation, ImGuizmo::LOCAL, glm::value_ptr(transform));

	if (ImGuizmo::IsUsing())
		return true;
	else
		return false;
}

void EditorLayerTest::ShowFpsOverlay(ImGuiViewport* viewport, const bool& show, const float& x, const float& y)
{
	if (show)
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
		ImGui::Begin("Example: Simple overlay", nullptr, window_flags);
		{
			ImGui::Text("Application average %.1f ms/frame (%.0f FPS)", 1000.0f / io.Framerate, io.Framerate);
		}
		ImGui::End();
	}
}
