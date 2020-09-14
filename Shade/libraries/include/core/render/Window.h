#pragma once
#include <SDL2/SDL.h>
#undef main // For SDL
#include <glad/glad.h>

#include <core/Definitions.h>
#include <utilities/Log.h>
#include <string>


namespace se {

	struct SE_API Window
	{
		std::string     Title  = "Shade Engine";
		unsigned int    Width  = WINDOW_WIDTH;
		unsigned int    Height = WINDOW_HEIGHT;
		SDL_Window*     Handle = nullptr;
		SDL_Event       Event;
		SDL_WindowFlags WindowFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		
	};

	class SE_API WindowManager
	{
		
	public:

		static void CreateWindow(Window& window);
		static void CreateWindow(Window&& window);
		static Window& GetWindow();
		static void Update();
		static inline bool IsClosed() { return GetInstance().m_IsClosed; } 
		static inline void Close()    { GetInstance()._Close(); }
	private:
		WindowManager();
		~WindowManager();
		//Delete copy and move constructor
		//Copy
		WindowManager(const WindowManager&) = delete;
		WindowManager& operator= (const WindowManager&) = delete;
		//Move
		WindowManager(const WindowManager&&) = delete;
		WindowManager& operator= (const WindowManager&&) = delete;
		//////////////////////////////////////

		static WindowManager& GetInstance();
		void    _CreateWindow(Window& window);
		void    _Close();
		Window& _GetWindow();
		void _Update();

		Window                        m_Window;
		SDL_DisplayMode               m_DisplayMode;
		SDL_GLContext                 m_Context;
		bool m_IsClosed;
	};
}


