#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/SDL2/SDL.h"
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Engine/Input.h"

#undef main // For SDL

namespace se
{
	// Forward Declaration
	class Layer;
	class Scene;
	//////////////////////

	typedef SDL_Event     Event;
	typedef SDL_EventType EventType;
	typedef SDL_KeyCode   KeyCode;

	using EventCallback = std::function<bool(Event const&)>;

	class SE_API EventManager
	{
		
	public:
		friend class Application;

		static int  RegAppEventCallback(const EventType& type, const EventCallback& callback);
		static int  RegSceneEventCallback(const EventType& type, const Scene* scene, const EventCallback& callback);
		static int  RegLayerEventCallback(const EventType& type, const Scene* scene, const Layer* layer, const EventCallback& callback);
		static void DeleteEventCallback(const EventType& type, int index);
		static void DeleteEventCallback(const EventType& type);
	private:
		//Singleton implementation
		EventManager();
		~EventManager();
		EventManager(const EventManager&) = delete;
		EventManager& operator= (const EventManager&) = delete;
		EventManager(const EventManager&&) = delete;
		EventManager& operator= (const EventManager&&) = delete;
		static EventManager& Get();
		/////////////////////////////////

		void Update();
		void EraseCallbacks();

		se::Event  m_Event;
		std::map<EventType, std::vector<EventCallback>> m_CoreCallbacks;
		std::map<EventType, std::map<const Scene*, std::vector<EventCallback>>> m_SceneCallbacks;
		std::map<EventType, std::map<const Scene*, std::map<const Layer*, std::vector<EventCallback>>>> m_LayerCallbacks;
	};
}


