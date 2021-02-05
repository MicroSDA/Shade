#include "stdafx.h"
#include "WindowManager.h"

se::WindowManager::WindowManager() :
	m_Context(nullptr), m_IsWindowCreated(false),
	m_ClearR(0), m_ClearG(0), m_ClearB(0), m_ClearA(1)
{
	
}

se::WindowManager::~WindowManager()
{
}

se::WindowManager& se::WindowManager::Get()
{
	static WindowManager _Instatnce;
	return _Instatnce;
}

void se::WindowManager::Create(const Window& window)
{
	if (se::System::IsVideoInit())
	{
		auto& _Manager = Get();
		if (_Manager.m_Window.Handler != nullptr)
			SDL_DestroyWindow(_Manager.m_Window.Handler);

		SDL_GetCurrentDisplayMode(0, &_Manager.m_DisplayMode);
		_Manager.m_Window = window;
		_Manager.m_Window.Handler = SDL_CreateWindow(
			_Manager.m_Window.Title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_Manager.m_Window.Width,
			_Manager.m_Window.Height,
			_Manager.m_Window.WindowFlags
		);

		_Manager.m_Context = SDL_GL_CreateContext(_Manager.m_Window.Handler);
		SDL_GL_MakeCurrent(_Manager.m_Window.Handler, _Manager.m_Context);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
			throw se::ShadeException((std::string("Glad initializing faild!") + SDL_GetError()).c_str(), se::SECode::Error);

		SetViewPort(0, 0, window.Width, window.Height);
		_Manager.m_IsWindowCreated = true;

		SE_DEBUG_PRINT(std::string("Display native resolution is:" + std::to_string(_Manager.m_DisplayMode.w) +
			"x" + std::to_string(_Manager.m_DisplayMode.h)).c_str(), SLCode::InfoSecondary);
	}
	else
	{
		throw se::ShadeException("Trying to create window but video has not been initialized yeat!", se::SECode::Error);
	}
	
}

void se::WindowManager::Update()
{

	if (!m_Window.IsClosed)
	{
		if (m_IsWindowCreated)
		{
			SDL_GL_SwapWindow(m_Window.Handler);
#ifdef SE_DEBUG
			static GLenum _GLError = glGetError();
			if (_GLError != GL_NO_ERROR)
				SE_DEBUG_PRINT((std::string("OpenGL Error: ") + std::to_string(_GLError)).c_str(), se::SLCode::Warning);
#endif // SE_DEBUG
		}
		else
		{
			throw se::ShadeException("Window has not been created!", se::SECode::Error);
		}
	}
	else
	{
		DestroyWindow();
	}
}

void se::WindowManager::DestroyWindow()
{
	auto& _Manager = Get();
	SDL_GL_DeleteContext(_Manager.m_Context);
	SDL_DestroyWindow(_Manager.m_Window.Handler);
	_Manager.m_IsWindowCreated = false;
}

const se::Window& const se::WindowManager::GetWindow()
{
	return Get().m_Window;
}

void se::WindowManager::Close()
{
	Get().m_Window.IsClosed = true;
}

bool se::WindowManager::IsClosed()
{
	return Get().m_Window.IsClosed;
}

void se::WindowManager::Clear()
{
	if (m_IsWindowCreated)
	{
		glClearColor(Get().m_ClearR, Get().m_ClearG, Get().m_ClearB, Get().m_ClearA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}	
	else
		throw se::ShadeException("Window has not been created!", se::SECode::Error);
}

void se::WindowManager::SetClearColor(const float& r, const float& g, const float& b, const float& a)
{
	m_ClearR = r;
	m_ClearG = g;
	m_ClearB = b;
	m_ClearA = a;
}

void se::WindowManager::Resize()
{
	static int _Width;
	static int _Height;
	SDL_GetWindowSize(Get().m_Window.Handler, &_Width, &_Height);
	SetViewPort(GetViewPort().x, GetViewPort().y, _Width, _Height);
	Get().m_Window.Width = _Width;
	Get().m_Window.Height = _Height;
}

void se::WindowManager::SetViewPort(const int& x, const int& y, const int& width, const int& height)
{
	Get().m_ViewPort.x = x;
	Get().m_ViewPort.y = y;
	Get().m_ViewPort.width = width;
	Get().m_ViewPort.height = height;

	glViewport(x, y, width, height);
}

const se::VeiwPort& se::WindowManager::GetViewPort()
{
	return Get().m_ViewPort;
}

const SDL_GLContext& se::WindowManager::GetContext()
{
	return Get().m_Context;
}
