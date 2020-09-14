#pragma once
#include <core/events/EventManager.h>
#include <core/engine/Scene.h>

namespace se {
	//Main App
	class SE_API Engine
	{
	public:
		//Start Engine
		static void Start();
		static inline void AddScene(const Scene* scene) { GetInstance()._AddScene(scene); }
	private:
		Engine();
		~Engine();
		//Delete copy and move constructor
		//Copy
		Engine(const Engine&) = delete;
		Engine& operator= (const Engine&) = delete;
		//Move
		Engine(const Engine&&) = delete;
		Engine& operator= (const Engine&&) = delete;
		////////////////////////////////////////////
		static Engine& GetInstance();
		void _Start();
		inline void _AddScene(const Scene* scene)
		{ 
			m_CurrentScene = scene;
			m_Scenes.insert(std::make_pair(scene->GetName(), scene)); 
		}


		void Prepare();
		void Run();
		void Render();
		void Stop();
		void Clean();

		std::map<std::string, const Scene*> m_Scenes;
		mutable const Scene* m_CurrentScene;
	};
}

