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
	void ShowSceneEntities();
	void ShowAssetDataList();
	void ShowMenu();
	void ShowLightningSource();

	uint32_t m_SelectedEntityID = 1;
};