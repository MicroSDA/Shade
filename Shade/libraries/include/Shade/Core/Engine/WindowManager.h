#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Util/ShadeException.h"
#include "Vendors/SDL2/SDL.h"
#include "Vendors/glad/glad.h"

#include "Shade/Core/Util/Log.h"

#undef main // For SDL

namespace se
{
	typedef SDL_Window      WindowHandler;
	typedef SDL_WindowFlags WindowFlags;

	struct Window
	{
		std::string    Title = "Shade";
		unsigned int   Width = 1000;
		unsigned int   Height = 800;
		WindowHandler* Handler = nullptr;
		WindowFlags    WindowFlags = static_cast<se::WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		bool           IsClosed = false;
	};

	class SE_API WindowManager
	{
		
	public:
		friend class Application;
		friend class Renderer;

		static void Create(const Window& window);
		static void DestroyWindow();
		static const se::Window& const GetWindow();
		static void Close();
		static bool IsClosed();
		static void Resize();
	private:
		//Singleton implementation
		WindowManager();
		~WindowManager();
		WindowManager(const WindowManager&) = delete;
		WindowManager& operator= (const WindowManager&) = delete;
		WindowManager(const WindowManager&&) = delete;
		WindowManager& operator= (const WindowManager&&) = delete;
		static WindowManager& Get();
		/////////////////////////////////
	
		bool m_IsWindowCreated;

		void Update();
		void Clear();
		void SetClearColor(const float& r, const float& g, const float& b, const float& a);

		Window                        m_Window;
		SDL_DisplayMode               m_DisplayMode;
		SDL_GLContext                 m_Context;

		float m_ClearR, m_ClearG, m_ClearB, m_ClearA;
	};
}


