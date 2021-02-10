#pragma once
#include <Shade/Core/Engine/ImGuiLayer.h>

class EditorLayerTest :public se::ImGuiLayer
{
public:
	EditorLayerTest(const std::string& name, se::Scene* scene);
	virtual ~EditorLayerTest();

	virtual void OnCreate() override;
	virtual void OnInit() override;
	virtual void OnUpdate(const se::Timer& deltaTime) override;
	virtual void OnRender() override;
	virtual void OnDelete() override;
private:
	void ShowMainMenu(const bool& show);
	void ShowEntitiesList(const bool& show);
	void ProcessEntities(se::Entity& entity);
	void ShowInspector(const bool& show);
	void ShowScene(const bool& show);

	void ShowTagComponent(se::Entity& entity, const bool& show);
	void ShowTransform3DComponent(se::Entity& entity, const bool& show);
	void ShowModel3DComponent(se::Entity& entity, const bool& show);
	void ShowMeshComponent(se::Entity& entity, const bool& show);
	void ShowMaterialComponent(se::Entity& entity, const bool& show);
	void ShowEnvironmentComponent(se::Entity& entity, const bool& show);

	bool ShowImGuizmo(glm::mat4& transform, const bool& show, const float& x, const float& y, const float& w, const float& h);
	void ShowFpsOverlay(ImGuiViewport* viewport, const bool& show, const float& x, const float& y);

	bool isMainMenuShow = true;
	bool isEntitiesListShow = true;
	bool isInspectorShow = true;
	bool isTagComponentShow = true;
	bool isTransform3DComponentShow = true;
	bool isModel3DComponentShow = true;
	bool isMaterialComponentShow = true;
	bool isEnvironmentComponentShow = true;
	bool isSceneShow = true;
	bool isFpsShow = true;

	se::Entity m_SelectedEntity;
};

