#ifdef _MSVC_LANG
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "stdafx.h"
#include "Shade/Core/Util/FileDialog.h"
#include "EditorLayer.h"

EditorLayer::EditorLayer(const std::string& name, se::Scene* scene) : se::ImGuiLayer(name, scene)
{
}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::OnCreate()
{
	/*se::EventManager::RegLayerEventCallback(se::EventType::SDL_KEYDOWN, GetScene(), this,
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
			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				m_SelectedEntity = se::Entity();
			}

			return false;
		});*/
}

void EditorLayer::OnInit()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("./resources/fonts/imgui/Ruda-Black.ttf", 17.0f);
}

void EditorLayer::OnUpdate(const se::Timer& deltaTime)
{
	// Changing scene veiw port
	auto entts = se::Application::GetApplication().GetEntities().view<glm::vec2, se::TagComponent>();
	for (auto& ent : entts)
	{
		se::Entity entity{ ent , &se::Application::GetApplication() };

		if (entity.IsValid())
		{
			if (entity.GetComponent<se::TagComponent>().Tag == "SceneViewPort")
			{
				m_MainSceneVeiwPort = entity;
			}
		}
	}
}

void EditorLayer::OnRender()
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

		this->ShowMainMenu(m_IsMainMenu);
		this->ShowProjectBar(m_IsProjectBar);
		this->ShowSceneWindow(m_IsSceneWindow);
	} ImGui::End(); // Begin("DockSpace")*/
}

void EditorLayer::OnDelete()
{

}

void EditorLayer::OnEvent(const se::Event& event)
{
	OnImGuiEvent(event);

	if (event.GetType() == se::Event::Type::KeyDown)
	{
		if (event.GetKeyboard().ScanCode == se::Event::Keyboard::SCode::F)
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
		else if (event.GetKeyboard().ScanCode == se::Event::Keyboard::SCode::Escape)
		{
			m_SelectedEntity = se::Entity();
		}
	}
}

void EditorLayer::ShowMainMenu(const bool& show)
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
					std::string filePath = se::FileDialog::OpenFile("Shade Scene (*.sahde)\0*.shade\0");
					if (filePath.size())
					{
						this->GetScene()->DestroyEntities();
						se::Serializer::DeserializeScene(filePath, *this->GetScene());
					}
				}

				if (ImGui::MenuItem("Save")) 
				{ 
					std::string filePath = se::FileDialog::OpenFile("Shade Scene (*.sahde)\0*.shade\0");
					if (filePath.size())
					{
						se::Serializer::SerializeScene(filePath, *this->GetScene());
					}
				}

				ImGui::Separator();
				if (ImGui::MenuItem("Exit"))  se::Application::GetApplication().Quit();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Options"))
			{
				ImGui::MenuItem("Project", "", &m_IsProjectBar);
				ImGui::MenuItem("Scene", "", &m_IsSceneWindow);
				ImGui::MenuItem("ImGuizmo", "", &m_IsImGuizmoShow);
				ImGui::MenuItem("FPS", "", &m_IsFpsShow);

				ImGui::EndMenu();
			}

		} ImGui::EndMenuBar();
	}
}

void EditorLayer::ShowProjectBar(const bool& show)
{
	if (show)
	{
		if (ImGui::Begin("Project"))
		{
			if (ImGui::TreeNode(std:: string("##" + GetScene()->GetName()).c_str(), std::string("Scene: " + GetScene()->GetName()).c_str()))
			{
				DrawEntities(m_SelectedEntity, this->GetScene());
				DrawInspector(m_SelectedEntity);
				ImGui::TreePop();
			}

			this->ShowAssetList(m_IsAssetListShow);

		} ImGui::End();
	}
}

void EditorLayer::ShowSceneWindow(const bool& show)
{
	if (show)
	{
		if (ImGui::Begin("Scene"))
		{
			auto frameBuffer = GetScene()->GetFrameBuffer("MainLayerFB");
			if (frameBuffer != nullptr)
			{
				auto& viewPortSize = m_MainSceneVeiwPort.GetComponent<glm::vec2>();

				if (viewPortSize.x != ImGui::GetContentRegionAvail().x
					|| viewPortSize.y != ImGui::GetContentRegionAvail().y)
				{
					viewPortSize.x = ImGui::GetContentRegionAvail().x;
					viewPortSize.y = ImGui::GetContentRegionAvail().y;

					//Create window resize event and grab it in MainLayer
					 se::Event event;
					 event.SetType(se::Event::Type::Window);
					 event.SetWindow(se::Event::Window::Resized);
					se::EventManager::PusEvent(event);
				}

				ImTextureID tid = reinterpret_cast<void*>(frameBuffer->GetTextureAttachment());
				ImGui::Image(tid, ImVec2{ viewPortSize.x, viewPortSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

				if (m_SelectedEntity.IsValid())
				{
					if (m_SelectedEntity.HasComponent<se::Transform3DComponent>())
					{
						auto transform_tmp = m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform.GetModelMatrix();

						if (this->ShowImGuizmo(transform_tmp, GetScene()->GetActiveCamera().get(), m_IsImGuizmoShow, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y))
						{
							glm::vec3 position, rotation, scale;
							ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform_tmp), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));

							auto& transform = m_SelectedEntity.GetComponent<se::Transform3DComponent>().Transform;
							transform.SetPostition(position);
							transform.SetRotation(glm::radians(rotation));
							transform.SetScale(scale);
						}
					}
					else if (m_SelectedEntity.HasComponent<se::EnvironmentComponent>())
					{
						ShowEnvironmentImGuizmo(m_SelectedEntity);
					}
				}

				this->ShowFPSOverlay(ImGui::GetWindowViewport(), m_IsFpsShow, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
			}

		} ImGui::End();
	}
}

void EditorLayer::ShowAssetList(const bool& show)
{
	if (show)
	{
		if (ImGui::Begin("Asset list"))
		{
			auto list = se::AssetManager::GetAssetDataList();
			for (auto& node : list._Dependency)
			{
				DrawAssetDataNode(node);
			}
			

		} ImGui::End();
	}
}

void EditorLayer::DrawEntities(se::Entity& selectedEntity, se::EntitiesDocker* docker)
{
	if (ImGui::TreeNodeEx("Entities", ImGuiTreeNodeFlags_SelectedWhenOpen))
	{
		ImGui::NewLine();
		if (ImGui::Button("New entity", ImVec2(ImGui::GetContentRegionAvailWidth(), 0)))
			ImGui::OpenPopup("##create_new_entity");
		CreateEntityModal("##create_new_entity", *docker);

		ImGui::NewLine();
		static char buffer[256] = "";
		ImGui::Text("Search"); ImGui::SameLine();
		ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
		ImGui::InputTextWithHint("##entities_search", "Entity name", buffer, sizeof(buffer));
		ImGui::PopItemWidth();
		if (ImGui::ListBoxHeader("##list", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y)))
		{
			GetScene()->GetEntities().each([&](auto entityID)
				{
					se::Entity entity{ entityID , docker };

					DrawEntity(entity, selectedEntity, buffer);
				});

			ImGui::ListBoxFooter();
		}
		ImGui::TreePop();

	
	}
}

void EditorLayer::DrawEntity(se::Entity& entity, se::Entity& selectedEntity, const std::string& filter)
{
	auto& name = entity.GetComponent<se::TagComponent>().Tag;

	if (filter.size())
	{
		if (filter.size() && name == filter)
		{
			if (ImGui::Selectable(std::string(name + "##" + entity).c_str(), selectedEntity == entity))
				selectedEntity = entity;
		}
	}
	else
	{
		if (ImGui::Selectable(std::string(name + "##" + entity).c_str(), selectedEntity == entity))
			selectedEntity = entity;
	}


	if (ImGui::BeginPopupContextItem())
	{
		//AddComponent<se::Transform3DComponent>("Transform3DComponent", entity);
		//AddComponent<se::Model3DComponent>("Model3DComponent", entity);
		//AddComponent<se::EnvironmentComponent>("EnvironmentComponent", entity);
		AddComponent<se::CameraComponent>("CameraComponent", entity, [&](se::CameraComponent& component) {
				AddCameraComponentCallback(component); 
			});


		ImGui::Separator();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7, 0, 0, 1));
		if (ImGui::MenuItem("Remove entity"))
			entity.Destroy();
		ImGui::PopStyleColor();

		ImGui::EndPopup();
	}
}


void EditorLayer::DrawInspector(se::Entity& entity)
{
	if (ImGui::Begin("Inspector##inspector"))
	{
		if (entity.IsValid())
		{
			DrawComponent<se::TagComponent>("Tag", entity, [&]()
				{
					TagCallback(entity);
				});
			DrawComponent<se::Transform3DComponent>("Transform3D", entity, [&]()
				{
					Transform3DCallback(entity);
				});
			DrawComponent<se::Model3DComponent>("Model3D", entity, [&]()
				{
					Model3DCallback(entity);
				});
			DrawComponent<se::EnvironmentComponent>("Environment", entity, [&]()
				{
					EnvironmentCallback(entity);
				});
			DrawComponent<se::CameraComponent>("Camera", entity, [&]()
				{
					CameraCallback(entity);
				});
		}
	}

	ImGui::End();
}

void EditorLayer::DrawAddComponentDelteEntity(se::Entity& entity)
{
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Add Component")) {}
		if (ImGui::MenuItem("Delete Entity")) {}
		ImGui::EndPopup();
	}
}

void EditorLayer::DrawAssetDataNode(se::AssetData& data)
{
	if (ImGui::TreeNodeEx(data._Name.c_str(), ImGuiTreeNodeFlags_SelectedWhenOpen))
	{
		if (!data._Name.empty())
			ImGui::TextWrapped("Name: %s", data._Name.c_str());
		if (!data._Path.empty())
			ImGui::TextWrapped("Path: %s", data._Path.c_str());
		

		for (auto& node : data._Dependency)
		{
			DrawAssetDataNode(node);
		}

		ImGui::TreePop();
	}
}

void EditorLayer::TagCallback(se::Entity& entity)
{
	static char buffer[256]; memset(buffer, 0, sizeof(buffer));
	auto& tag = entity.GetComponent<se::TagComponent>().Tag;
	std::strncpy(buffer, tag.c_str(), sizeof(buffer));

	if (ImGui::InputTextWithHint("##Tag", tag.c_str(), buffer, sizeof(buffer)))
		tag = std::string(buffer);
}

void EditorLayer::Transform3DCallback(se::Entity& entity)
{
	auto& transform = entity.GetComponent<se::Transform3DComponent>().Transform;
	DrawFloatVec3("Position", glm::value_ptr(transform.GetPosition()));
	DrawFloatVec3("Roatation", glm::value_ptr(transform.GetRotation()));
	DrawFloatVec3("Scale", glm::value_ptr(transform.GetScale()));
}

void EditorLayer::Model3DCallback(se::Entity& entity)
{
	auto* pModel = entity.GetComponent<se::Model3DComponent>().Model3D.get();
	if (pModel != nullptr)
	{
		// Drwaing tag agin it's only for nice TreeNode
		DrawComponent<se::TagComponent>("Meshes", entity, [&]()
			{
				pModel->GetEntities().each([&](auto entityID)
					{
						se::Entity entity{ entityID , pModel };
						DrawComponent<se::MeshComponent>(entity.GetComponent<se::TagComponent>().Tag.c_str(), entity, [&]()
							{
								MeshCallback(entity);
							});
					});
			});
	}
}

void EditorLayer::MeshCallback(se::Entity& entity)
{
	DrawComponent<se::TagComponent>("Tag", entity, [&]()
		{
			TagCallback(entity);
		});
	DrawComponent<se::MaterialComponent>("Material", entity, [&]()
		{
			MaterialCallback(entity);
		});
}

void EditorLayer::TextureCallback(se::Entity& entity)
{
	const float width = 100.0f, height = 100.0f;
	auto texture = entity.GetComponent<se::TextureComponent>().Texture;
	ImTextureID tid = reinterpret_cast<void*>(texture->GetTextureRenderId());
	uint32_t id = entity;

	switch (texture->GetAssetData()._SubType)
	{
	case se::AssetDataSubType::Diffuse:
		ImGui::BulletText("Type: Diffuse");
		break;
	case se::AssetDataSubType::Specular:
		ImGui::BulletText("Type: Specular");
		break;
	case se::AssetDataSubType::NormalMap:
		ImGui::BulletText("Type: NormalMap");
		break;
	}

	ImGui::Image(tid, ImVec2{ width, height }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
}

void EditorLayer::MaterialCallback(se::Entity& entity)
{
	auto& material = entity.GetComponent<se::MaterialComponent>().Material;
	float tab_width = 145.0f;
	DrawColor3("Ambient", glm::value_ptr(material.GetAmbientColor()), tab_width);
	DrawColor3("Diffuse", glm::value_ptr(material.GetDiffuseColor()), tab_width);
	DrawColor3("Scpecular", glm::value_ptr(material.GetSpecularColor()), tab_width);
	DrawFloat("Shininess", &material.GetShininess(), 0.0f, -FLT_MAX, FLT_MAX, tab_width);
	DrawFloat("Shininess strength", &material.GetShininessStrength(), 0.0f, -FLT_MAX, FLT_MAX, tab_width);

	auto& mesh = entity.GetComponent<se::MeshComponent>().Mesh;

	DrawComponent<se::TagComponent>("Textures", entity, [&]
		{
			mesh->GetEntities().each([&](auto entityID)
				{
					se::Entity entity{ entityID , mesh.get() };
					std::string name = entity.GetComponent<se::TagComponent>().Tag + "##" + entity;

					DrawComponent<se::TagComponent>(name.c_str(), entity, [&]
						{
							TextureCallback(entity);
						});
				});
		});
	
}

void EditorLayer::EnvironmentCallback(se::Entity& entity)
{
	auto& env = entity.GetComponent<se::EnvironmentComponent>().Environment;
	switch (env->GetType())
	{
	case se::Environment::Type::GeneralLight:
	{
		m_GuizmoOperation = ImGuizmo::OPERATION::ROTATE;
		auto pLight = static_cast<se::GeneralLight*>(env.get());
		ImGui::BulletText("Type: %s", "General light");
		this->DrawFloatVec3("Direction", glm::value_ptr(pLight->GetDirection()), 0.0, -1.0f, 1.0f);
		this->DrawColor3("Ambient", glm::value_ptr(pLight->GetAmbientColor()));
		this->DrawColor3("Diffuse", glm::value_ptr(pLight->GetDiffuseColor()));
		this->DrawColor3("Specular", glm::value_ptr(pLight->GetSpecularColor()));
		break;
	}
	case se::Environment::Type::PointLight:
	{
		m_GuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		auto pLight = static_cast<se::PointLight*>(env.get());
		ImGui::BulletText("Type: %s", "Point light");
		this->DrawFloatVec3("Position", glm::value_ptr(pLight->GetPosition()), 0.0);
		this->DrawColor3("Ambient", glm::value_ptr(pLight->GetAmbientColor()));
		this->DrawColor3("Diffuse", glm::value_ptr(pLight->GetDiffuseColor()));
		this->DrawColor3("Specular", glm::value_ptr(pLight->GetSpecularColor()));
		this->DrawFloat("Constant", &pLight->GetConstant(), 1.0f);
		this->DrawFloat("Linear", &pLight->GetLinear(), 0.0f);
		this->DrawFloat("Qaudratic", &pLight->GetQaudratic(), 0.0f);
		break;
	}
	case se::Environment::Type::SpotLight:
	{

		break;
	}
	default:

		break;
	}
}

void EditorLayer::CameraCallback(se::Entity& entity)
{
	auto& camera = entity.GetComponent<se::CameraComponent>().Camera;
	DrawFloatVec3("Position", glm::value_ptr(camera->GetPosition()));
	DrawFloatVec3("Dirrection", glm::value_ptr(camera->GetForwardDirrection()), -1.0, 1, 0);
	if (DrawFloat("Fov", &camera->GetFov(), 45.0))
		camera->Resize();

	if (entity.HasComponent<se::NativeScriptComponent>())
	{
		auto instance = entity.GetComponent<se::NativeScriptComponent>().Instance;

		if (instance)
		{
			auto free_camera = dynamic_cast<se::FreeCameraController*>(instance);
			if (!free_camera)
			{
				if (ImGui::Button("Free move"))
				{

				}
			}
		}
		else
		{
			if (ImGui::Button("Free move"))
			{

			}
		}
	}
	else
	{
		if (ImGui::Button("Free move"))
		{

		}
	}


	
}

void EditorLayer::AddCameraComponentCallback(se::CameraComponent& component)
{
	auto pCamera = new se::Camera();
	auto aspect = m_MainSceneVeiwPort.GetComponent<glm::vec2>();
	pCamera->Resize( aspect.x / aspect.y);
	component.IsPrimary = true;
	component.Camera = se::ShadeShared<se::Camera>(pCamera);
}

bool EditorLayer::DrawColor3(const char* lable, float* data, const float& cw1, const float& cw2)
{
	ImGui::PushID(lable);
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, cw1);
	if (cw2 > 0.0f)
		ImGui::SetColumnWidth(1, cw2);

	ImGui::Text(lable);
	ImGui::NextColumn();
	ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
	bool isUsed = ImGui::ColorEdit3("##color", data);
	ImGui::PopItemWidth();
	ImGui::Columns(1);
	ImGui::PopID();

	return isUsed;
}

bool EditorLayer::DrawFloatVec3(const char* lable, float* data, const float& reset, const float& min, const float& max, const float& cw1)
{
	bool isUsed = false;

	ImGui::PushID(lable);
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, cw1);
	ImGui::Text(lable);
	ImGui::NextColumn();

	if (ImGui::Button("X")) { data[0] = reset; isUsed = true; }

	const ImGuiStyle& style = ImGui::GetStyle();
	ImVec2 label_size = ImGui::CalcTextSize("X", NULL, true);
	ImVec2 button_size = CalcItemSize(ImVec2(0, 0), label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
	float width = (ImGui::GetContentRegionAvailWidth() - ((cw1 + style.FramePadding.x * 3) / 2) - ((button_size.x - style.FramePadding.x) * 3)) / 3;

	ImGui::SameLine();
	ImGui::PushItemWidth(width);
	if (ImGui::DragFloat("##X", &data[0], 0.01f, min, max, "%.2f"))
		isUsed = true;

	ImGui::PopItemWidth();
	ImGui::SameLine();

	if (ImGui::Button("Y")) { data[1] = reset; isUsed = true; } ImGui::SameLine();
	ImGui::PushItemWidth(width);
	if (ImGui::DragFloat("##Y", &data[1], 0.01f, min, max, "%.2f"))
		isUsed = true;

	ImGui::PopItemWidth();
	ImGui::SameLine();

	if (ImGui::Button("Z")) { data[2] = reset; isUsed = true; } ImGui::SameLine();
	ImGui::PushItemWidth(width);
	if (ImGui::DragFloat("##Z", &data[2], 0.01f, min, max, "%.2f"))
		isUsed = true;

	ImGui::PopItemWidth();
	ImGui::Columns(1);
	ImGui::PopID();

	return isUsed;
}

bool EditorLayer::DrawFloat(const char* lable, float* data, const float& reset, const float& min, const float& max, const float& cw1, const float& cw2)
{
	ImGui::PushID(lable);
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, cw1);
	if (cw2 > 0.0f)
		ImGui::SetColumnWidth(1, cw2);

	ImGui::Text(lable);
	ImGui::NextColumn();
	ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
	bool isUsed = ImGui::DragFloat("##value", data, 0.01f, -FLT_MAX, FLT_MAX, "%.4f");
	ImGui::PopItemWidth();
	ImGui::Columns(1);
	ImGui::PopID();

	return isUsed;
}

void EditorLayer::ShowEnvironmentImGuizmo(se::Entity& entity)
{
	auto environment = entity.GetComponent<se::EnvironmentComponent>().Environment.get();
	switch (environment->GetType())
	{
	case se::Environment::Type::Environment:
		break;
	case se::Environment::Type::GeneralLight:
	{
		auto pLight = static_cast<se::GeneralLight*>(environment);
		glm::mat4 transform = glm::toMat4(glm::quat((pLight->GetDirection())));

		if (this->ShowImGuizmo(transform, GetScene()->GetActiveCamera().get(), m_IsImGuizmoShow, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y))
		{
			glm::vec3 position, rotation, scale;
			ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));
			pLight->SetDirection(glm::radians(rotation)); // TODO: Normalize
		}
		break;
	}
	case se::Environment::Type::PointLight:
	{
		auto pLight = static_cast<se::PointLight*>(environment);

		glm::mat4 transform = glm::translate(pLight->GetPosition());
		if (this->ShowImGuizmo(transform, GetScene()->GetActiveCamera().get(),m_IsImGuizmoShow, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y))
		{
			glm::vec3 position, rotation, scale;
			ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));
			pLight->SetPosition(position);
		}

		break;
	}
	case se::Environment::Type::SpotLight:
		auto pLight = static_cast<se::SpotLight*>(environment);

		glm::mat4 translate = glm::translate(pLight->GetPosition());
		glm::mat4 rotate = glm::toMat4(glm::quat(pLight->GetDirection()));
		glm::mat4 transform = translate * rotate;
		if (this->ShowImGuizmo(transform, GetScene()->GetActiveCamera().get(), m_IsImGuizmoShow, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y))
		{
			glm::vec3 position, rotation, scale;
			ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));
			pLight->SetPosition(position);
			pLight->SetDirection(glm::radians(rotation));
		}
		break;
	}
}

void EditorLayer::CreateEntityModal(const char* modalName, se::EntitiesDocker& docker)
{
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal(modalName, NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize))
	{

		static char buffer[256] = "";
		ImGui::Text("Name"); ImGui::SameLine();
		ImGui::PushItemWidth(400);
		ImGui::InputTextWithHint("##new_entity_name", "Entity name", buffer, sizeof(buffer));
		ImGui::PopItemWidth();
		ImGui::NewLine();

		if (ImGui::Button("Create"))
		{
			if (strcmp(buffer, "") == 1)
			{
				docker.CreateEntity(buffer);
				memset(buffer, 0, sizeof(buffer));
				ImGui::CloseCurrentPopup();
			}
		}


		ImGui::SameLine();
		if (ImGui::Button("Close"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

