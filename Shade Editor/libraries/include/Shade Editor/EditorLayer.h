#pragma once
#include <Shade/Core/Engine/ImGuiLayer.h>

class EditorLayer :public se::ImGuiLayer
{
public:
	EditorLayer(const std::string& name, se::Scene* scene);
	virtual ~EditorLayer();

	virtual void OnCreate() override;
	virtual void OnInit() override;
	virtual void OnUpdate(const se::Timer& deltaTime) override;
	virtual void OnRender() override;
	virtual void OnDelete() override;
private:
	void ShowMainMenu(const bool& show);
	void ShowEntitiesList(const bool& show);
	void ProcessEntities(const std::string& filter, se::Entity& entity, se::Entity& selectedEntity);
	void ShowInspector(const bool& show);
	void ShowScene(const bool& show);
	void ShowProject(const bool& show);

	void ShowTagComponent(se::Entity& entity);
	void ShowTransform3DComponent(se::Entity& entity);
	void ShowModel3DComponent(se::Entity& entity);

	void ShowMeshComponent(se::Entity& entity, const bool& show);
	void ShowMaterialComponent(se::Entity& entity, se::MeshComponent& mesh, const bool& show);
	void ShowTextureComponent(se::Entity& entity, const bool& show);
	void ShowEnvironmentComponent(se::Entity& entity, const bool& show);
	void ShowCameraComponent(se::Entity& entity, const bool& show);

	bool ShowImGuizmo(glm::mat4& transform, const bool& show, const float& x, const float& y, const float& w, const float& h);
	void ShowFpsOverlay(ImGuiViewport* viewport, const bool& show, const float& x, const float& y);

	void NewEntityModal(se::EntitiesDocker& docker);
	void CreateEntity(se::EntitiesDocker& docker, const std::string& name);
	void DeletEntity(se::EntitiesDocker& docker, se::Entity& entity);
	void AddComponentModal(se::Entity& entity);
	template<typename T>
	T& AddComponent(se::Entity& entity)
	{
		return entity.AddComponent<T>();
	}
	template<typename T>
	void RemoveComponent(se::Entity& entity)
	{
		return entity.RemoveComponent<T>();
	}

	template<typename T, typename C>
	void DrawComponent(const char* name, se::Entity& entity, const bool& isShow, C callback)
	{
		if (isShow)
		{
			if (entity.HasComponent<T>())
			{
				if (ImGui::TreeNode(name))
				{
					callback();
					ImGui::TreePop();
				}
			}
		}
	}
	bool isMainMenuShow = true;
	bool isProjectShow = true;
	bool isEntitiesListShow = true;
	bool isInspectorShow = true;
	bool isTagComponentShow = true;
	bool isTransform3DComponentShow = true;
	bool isModel3DComponentShow = true;
	bool isMaterialComponentShow = true;
	bool isTextureComponentShow = true;
	bool isEnvironmentComponentShow = true;
	bool isCameraComponentShow = true;
	bool isSceneShow = true;
	bool isFpsShow = true;

	se::Entity m_SelectedEntity;
};

