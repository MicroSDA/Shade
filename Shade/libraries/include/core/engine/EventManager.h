#pragma once
#include <core/engine/Engine.h>

#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <string>

class Layer;
namespace se
{
	
	//For event creating and managment
	class SE_API EventManager
	{
		friend class se::Engine;
		
	public:
		static int  RegisterEventCoreCallback(const EventType& type, const EventCallback& callback);
		static int  RegisterSceneCallback(const EventType& type, const Scene* ,const EventCallback& callback);
		static int  RegisterLayerCallback(const EventType& type, const Scene* scene, const Layer* layer, const EventCallback& callback);
		static void DeleteCallback(const EventType& type, int index);
		static void DeleteCallback(const EventType& type);
	private:
		//Singleton implementation
		EventManager();
		~EventManager();
		EventManager(const EventManager&) = delete;
		EventManager& operator= (const EventManager&) = delete;
		EventManager(const EventManager&&) = delete;
		EventManager& operator= (const EventManager&&) = delete;
		static EventManager& GetInstance();
		/////////////////////////////////
		void Update();
		int  _RegisterEventCoreCallback(const EventType& type, const EventCallback& callback);
		int  _RegisterSceneCallback(const EventType& type, const Scene* scene, const EventCallback& callback);
		int  _RegisterLayerCallback(const EventType& type, const Scene* scene, const Layer* layer, const EventCallback& callback);
		
		void EraseCallbacks();
		Event  m_Event;
		std::map<EventType, std::vector<EventCallback>> m_CoreCallbacks;
		std::map<EventType, std::map<const Scene* ,std::vector<EventCallback>>> m_SceneCallbacks;
		std::map < EventType, std::map<const Scene*, std::map<const Layer*, std::vector<EventCallback>>>> m_LayerCallbacks;
	};
}
