#pragma once

#include <Shade/Utilities/Log.h>
#include <Shade/Core/Engine/Scene.h>
#include <Shade/Core/Engine/Window.h>

#include <string>
#include <map>

namespace se {

	
	//Main App
	struct SE_API EngineConfig
	{
		Window window;
		Scene* scene = nullptr;
	};

	enum class EngineState
	{
		RUNNING,
		PAUSE,
		STOP
	};

	class SE_API Engine
	{
	public:
		friend void Scene::SetScene(const std::string& name);
		
		static void SetConfig(const EngineConfig& config);
		static void SetState(const EngineState& state);
		inline static EngineState GetState() { return GetInstance().m_State; }
		//Start Engine
		static void Init();
		static void RegisterEventCallback(const EventType& type, const se::EventCallback& callback);
		static inline Scene* GetCurrentScene() { return GetInstance()._GetCurrentScene(); }
	private:
		
		//Singleton implementation
		Engine();
		~Engine();
		Engine(const Engine&) = delete;
		Engine& operator= (const Engine&) = delete;
		Engine(const Engine&&) = delete;
		Engine& operator= (const Engine&&) = delete;
		static Engine& GetInstance();

		void _SetConfig(const EngineConfig& config);
		void _SetState(const EngineState& state);
		void _Init();
		void _RegisterEventCallback(const EventType& type, const se::EventCallback& callback);
		inline Scene* _GetCurrentScene() const { return m_CurrentScene; }

		void Start();
		void Prepare();
		void Stop();
		void Update();
		void Termintae();

		EngineConfig                  m_Config;
		EngineState                   m_State;
		Scene*                        m_CurrentScene;
		std::map<std::string, Scene*> m_Scenes;
	};
}

