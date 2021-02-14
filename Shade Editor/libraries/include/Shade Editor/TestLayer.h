#pragma once
#include <Shade/Core/Engine/ImGuiLayer.h>

class TestLayer :public se::ImGuiLayer
{
public:
	TestLayer(const std::string& name, se::Scene* scene);
	virtual ~TestLayer();

	virtual void OnCreate() override;
	virtual void OnInit()   override;
	virtual void OnUpdate(const se::Timer& deltaTime) override;
	virtual void OnRender() override;
	virtual void OnDelete() override;
private:

	void ShowMainMenu(const bool& show);
	void ShowProjectBar(const bool& show);
	void ShowSceneWindow(const bool& show);

	void DrawEntities(se::Entity& selectedEntity, se::EntitiesDocker* docker);
	void DrawEntity(se::Entity& entity, se::Entity& selectedEntity, const std::string& filter = "");
	void DrawInspector(se::Entity& entity);
	void DrawAddComponentDelteEntity(se::Entity& entity);

	void TagCallback(se::Entity& entity);
	void Transform3DCallback(se::Entity& entity);
	void Model3DCallback(se::Entity& entity);
	void EnvironmentCallback(se::Entity& entity);
	void CameraCallback(se::Entity& entity);

	bool DrawColor3(const char* lable, float* data, const float& cw1 = 80.0f, const float& cw2 = 0);
	bool DrawFloatVec3(const char* lable, float* data, const float& reset = 0.0f, const float& min = -FLT_MAX, const float& max = FLT_MAX, const float& cw1 = 80.0f);
	bool DrawFloat(const char* lable, float* data, const float& reset = 0.0f, const float& min = -FLT_MAX, const float& max = FLT_MAX, const float& cw1 = 80.0f, const float& cw2 = 0);
	template<typename T, typename Callback>
	void DrawComponent(const char* name, se::Entity& entity, Callback callback, const bool& isShow = true)
	{
		if (isShow)
		{
			if (entity.HasComponent<T>())
			{
				std::string n = std::string(name) + "##" + std::string(entity);
				if (ImGui::TreeNode(n.c_str()))
				{
					callback();
					ImGui::TreePop();
				}
			}
		}
	};
	template<typename T>
	T& AddComponent(const char* componentName, se::Entity& entity)
	{
		if (!entity.HasComponent<T>())
		{
			if (ImGui::MenuItem(componentName))
				return entity.AddComponent<T>();
		}

		return *static_cast<T*>(nullptr);
	}

	bool m_IsMainMenu     = true;
	bool m_IsProjectBar   = true;
	bool m_IsSceneWindow  = true;
	bool m_IsImGuizmoShow = true;
	bool m_IsFpsShow	  = true;
	se::Entity  m_SelectedEntity;
	se::Entity  m_MainSceneVeiwPort;
};

