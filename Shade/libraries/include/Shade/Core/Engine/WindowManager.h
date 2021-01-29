#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Util/ShadeException.h"
#include "Shade/Core/Engine/System.h"
#include "Shade/Core/Util/Log.h"

namespace se
{
	typedef SDL_Window      WindowHandler;
	typedef SDL_WindowFlags WindowFlags;

	struct VeiwPort
	{
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
	};
	struct Window
	{
		std::string    Title = "Shade";
		unsigned int   Width = 1920;
		unsigned int   Height = 1000;
		WindowHandler* Handler = nullptr;
		WindowFlags    WindowFlags = static_cast<se::WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
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
		static void SetViewPort(const int& x, const int& y, const int& width, const int& height);
		static const se::VeiwPort& GetViewPort();
		static const SDL_GLContext& GetContext();
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

		se::VeiwPort                      m_ViewPort;
		se::Window                        m_Window;
		SDL_DisplayMode                   m_DisplayMode;
		SDL_GLContext                     m_Context;

		float m_ClearR, m_ClearG, m_ClearB, m_ClearA;
	};
}


