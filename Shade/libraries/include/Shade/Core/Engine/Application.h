#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Util/ShadeException.h"

#include "Shade/Core/Engine/Scene.h"
#include "Shade/Core/Engine/WindowManager.h"
#include "Shade/Core/Engine/EventManager.h"
#include "Shade/Core/Engine/AssetManager.h"
#include "Shade/Core/Engine/Timer.h"
#include "Shade/Core/Engine/EntitiesDocker.h"
#include "Shade/Core/Engine/Event.h"

namespace se
{
	//class Scene;
	class SE_API Application : public se::EntitiesDocker
	{
	public:
		Application();
		virtual ~Application();
		static Application& GetApplication();
		inline se::Scene* GetCurrentScene() const  { return m_pCurrentScene; };
		se::Scene* GetScene(const std::string& name);
		void   Start();
		void   Quit();
		virtual void OnInit() = 0; // TODO create runnecr class
	protected:
		virtual void OnUpdate(const se::Timer& deltaTime) = 0;
		virtual void OnEvent(const se::Event& event) = 0;
		void InitScene(const std::string& name);
		void SetCurentScene(const std::string& name);
		void DeleteScene(const std::string& name);
		std::unordered_map<std::string, se::Scene*>& GetScenes();
		void UpdateNativeScripts(const se::Timer& deltaTime);
		template<typename T>
		T* CreateScene(const std::string& name);

		friend class EventManager;
	private:
		std::unordered_map<std::string, se::Scene*> m_Scenes;
		static Application*                         m_pInstance;
		se::Scene*                                  m_pCurrentScene;
		bool                                        m_IsQuitRequested;
	};

	Application* CreateApplication();

	template<typename T>
	inline T* Application::CreateScene(const std::string& name)
	{
		auto pScene = static_cast<se::Scene*>(new T(name));
		pScene->OnCreate();
		SE_DEBUG_PRINT((std::string("Scene: '") + name + "' has been created!").c_str(), se::SLCode::InfoSecondary);

		m_Scenes.insert(std::pair<std::string, Scene*>(name, pScene));
		return static_cast<T*>(pScene);
	}


}

