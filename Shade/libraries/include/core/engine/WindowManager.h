#pragma once
#include <core/engine/Engine.h>
#include <core/engine/EventManager.h>
#include <core/engine/Window.h>

#include <glad/glad.h>

#include <utilities/Log.h>
#include <string>


namespace se
{
	//For window creating and managment
	class SE_API WindowManager
	{
		friend class se::Engine;
		

	public:
		//Window
		static void CreateWindow(Window& window);
		inline static bool IsClosed() { return GetInstance().m_Window.IsClosed; }
		inline static void Close()    { GetInstance().m_Window.IsClosed = true; }
		static void DestroyWindow();
	private:
		//Singleton implementation
		WindowManager();
		~WindowManager();
		WindowManager(const WindowManager&) = delete;
		WindowManager& operator= (const WindowManager&) = delete;
		WindowManager(const WindowManager&&) = delete;
		WindowManager& operator= (const WindowManager&&) = delete;
		static WindowManager& GetInstance();
		/////////////////////////////////
		void Update();
		void _CreateWindow(Window& window);
		void _DestroyWindow();

		Window                        m_Window;
		SDL_DisplayMode               m_DisplayMode;
		SDL_GLContext                 m_Context;
	};
}


