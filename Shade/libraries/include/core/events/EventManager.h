#pragma once
#include <core/render/Window.h>
#include <functional>
#include <vector>
#include <map>

namespace se {

	enum EventType : uint8_t
	{
		None = 0,
		WindowMoved = 4, WindowResized = 5, WindowClosed = 14,
		KyePressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMove
	};

	enum EventCategory : uint32_t
	{
		NONE = 0,
		CORE,
		ENGINE,
		WINDOW,
		KEYBOARD,
		MOUSE,

		COUNT = 7
	};

	class SE_API Event
	{
	public:
		Event(const EventCategory& category, const EventType& type)
			:category(category), type(type)
		{
		}

		virtual ~Event() {}

		EventCategory category;
		EventType     type;


	private:
	};

	class SE_API EventManager
	{
	public:
		inline static void OnEvent(const EventCategory& catagory, const std::function<bool()>& callBack);
		static void Update();
		
	private:
		EventManager();
		~EventManager();
		//Delete copy and move constructor
		//Copy
		EventManager(const EventManager&) = delete;
		EventManager& operator= (const EventManager&) = delete;
		//Move
		EventManager(const EventManager&&) = delete;
		EventManager& operator= (const EventManager&&) = delete;
		//////////////////////////////////////

		static EventManager& GetInstance();

		void _OnEvent(const EventCategory& catagory, const std::function<bool()>& callBack);

		void _Update();
		std::vector<std::function<bool()>> m_EventCallBacks[EventCategory::COUNT];

		
	};

	class EventHandler {
	public:
		using EventCallback = std::function<void(SDL_Event const&)>;

		void Register(SDL_EventType type, EventCallback callback) {
			_registeredCallbacks[type].push_back(callback);
		}

		void handleEvents() {
			SDL_Event event;
			while (SDL_PollEvent(&event) != 0) {
				for (auto& cb : _registeredCallbacks[static_cast<SDL_EventType>(event.type)]) {
					cb(event);
				}
			}
		}

	private:
		std::map<SDL_EventType, std::vector<EventCallback>> _registeredCallbacks;
	};

	class GameManager {
	public:

		void registerWithEventHandler(EventHandler& handler) {
			handler.Register(SDL_KEYUP, [this](SDL_Event const& event) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					SDL_Quit();
				}
				});
			handler.Register(SDL_QUIT, [this](SDL_Event const& event) {
				SDL_Quit();
				});
		}

	};
}

