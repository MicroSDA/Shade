#pragma once
#include <Shade/Utilities/Log.h>
#include <Shade/Core/Engine/Engine.h>
#include <Shade/Core/Engine/EventManager.h>
#include <Shade/Core/Engine/Window.h>
#include <Shade/Vendors/glad/glad.h>

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
		inline static bool IsClosed();
		inline static void Close();
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
		void Clear();
		void _CreateWindow(Window& window);
		void _DestroyWindow();

		Window                        m_Window;
		SDL_DisplayMode               m_DisplayMode;
		SDL_GLContext                 m_Context;
	};
}


