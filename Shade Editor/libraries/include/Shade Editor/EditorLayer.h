#pragma once
#include <Shade/Core/Engine/ImGuiLayer.h>

class EditorLayer :public se::ImGuiLayer
{
public:
	EditorLayer(const std::string& name, se::Scene* scene);
	virtual ~EditorLayer();
	// Inherited via Layer
	virtual void OnCreate() override;
	virtual void OnInit() override;
	virtual void OnUpdate(const se::Timer& deltaTime) override;
	virtual void OnRender() override;
	virtual void OnDelete() override;
private:
	void ShowMainScene();
	void ShowEntities();
	void ShowEntitiesInspector();
	void ShowGuizmo();
	void ShowAssetDataList();
	void ShowMenu();
	void ShowLightningSource();
	void ShowFpsOverlay(ImGuiViewport* viewport, const float& x, const float& y);

	void DrawEntity(const se::Entity& entity);
	
	se::Entity m_SelectedEntity;
	uint32_t m_SelectedEntityID = 0;
};