#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Util/ShadeException.h"

#include "Shade/Core/Engine/Scene.h"
#include "Shade/Core/Engine/WindowManager.h"
#include "Shade/Core/Engine/EventManager.h"
#include "Shade/Core/Engine/AssetManager.h"
#include "Shade/Core/Engine/Timer.h"

namespace se
{
	//class Scene;
	class SE_API Application
	{
	public:
		Application();
		virtual ~Application();
		static Application& GetApplication();
		inline se::Scene* GetCurrentScene() const  { return m_pCurrentScene; };
		virtual void OnInit() = 0;
		void   Start();
		void   Quit();
	protected:
		virtual void OnUpdate(const se::Timer& deltaTime) = 0;
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
		void SetCurentScene(const std::string& name);
		void DeleteScene(const std::string& name);
	private:
		static Application*               m_pInstance;
		se::Scene*                        m_pCurrentScene;
		std::map<std::string, se::Scene*> m_Scenes;
		bool                              m_IsQuitRequested;
	};

	Application* CreateApplication();
}

