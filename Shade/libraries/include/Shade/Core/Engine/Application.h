#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Util/ShadeException.h"

#include "Shade/Core/Engine/Scene.h"
#include "Shade/Core/Engine/WindowManager.h"
#include "Shade/Core/Engine/EventManager.h"
#include "Shade/Core/Engine/AssetManager.h"

namespace se
{
	//class Scene;
	class SE_API Application
	{
	public:
		Application();
		virtual ~Application();
		static Application& GetApp() { return *m_pInstance; }
		inline const se::Scene* GetActiveScene() const { return m_ActiveScene; };
		virtual void OnInit() = 0;
		void   Start();
	protected:
		virtual void OnUpdate() = 0;
		template<typename T>
		se::Scene* CreateScene(const std::string& name)
		{
			auto _Scene = static_cast<se::Scene*>(new T(name));
			_Scene->OnCreate();
			SE_DEBUG_PRINT((std::string("Scene: '") + name + "' has been created!").c_str(), se::SLCode::InfoSecondary);
			m_Scenes.insert(std::pair<std::string, Scene*>(name, _Scene));
			return _Scene;
		}
		std::map<std::string, se::Scene*>& GetScenes();
		se::Scene* GetScene(const std::string& name);
		void InitScene(const std::string& name);
		void SetActiveScene(const std::string& name);
		void DeleteScene(const std::string& name);
	private:
		static Application*               m_pInstance;

		se::Scene*                        m_ActiveScene;
		std::map<std::string, se::Scene*> m_Scenes;
	};

	Application* CreateApplication();
}

