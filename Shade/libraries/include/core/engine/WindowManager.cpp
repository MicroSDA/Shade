#include "WindowManager.h"

se::WindowManager::WindowManager()
{
}

se::WindowManager::~WindowManager()
{
}

se::WindowManager& se::WindowManager::GetInstance()
{
	static WindowManager _Instatnce;
	return _Instatnce;
}


void se::WindowManager::CreateWindow(Window& window)
{
	try
	{
		GetInstance()._CreateWindow(window);
	}
	catch (std::runtime_error& error)
	{
#ifdef SE_DEBUG
		DEBUG_PRINT(error.what(), LogLevel::ERROR);
#else 
		DEBUG_SAVE(error.what(), LogLevel::ERROR);
#endif // SE_DEBUG
		exit(-1);
	}
	
}

void se::WindowManager::_CreateWindow(Window& window)
{
	m_Window = window;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		//Im not sure if this works	!
		std::string msg = "Exeption : Video initializen faild in WindowManager::CreateWindow()", SDL_GetError();
		throw std::runtime_error(msg);
	}
		
	//TODO: If opnegl, if direct nad ect...

	//Set Opengl Version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	////////////////////////////////////////////////////

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	SDL_GetCurrentDisplayMode(0, &m_DisplayMode);

	m_Window.Handler = SDL_CreateWindow(
		m_Window.Title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_Window.Width,
		m_Window.Height,
		m_Window.WindowFlags
	);

	m_Context = SDL_GL_CreateContext(m_Window.Handler);

	SDL_GL_MakeCurrent(m_Window.Handler, m_Context);

	//SDL_GL_SetSwapInterval(-1);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		throw std::runtime_error("Exeption : Glad initializing faild");
	}

	DEBUG_PRINT("Display native resolution is:" + std::to_string(m_DisplayMode.w) +
		"x" + std::to_string(m_DisplayMode.h), LogLevel::INFO_SECONDARY);

}

void se::WindowManager::Update()
{
	if (m_Window.IsClosed)
	{
		_DestroyWindow();
	}
	else
	{
		SDL_GL_SwapWindow(m_Window.Handler);

#ifdef SE_DEBUG
		static GLenum _GLError = glGetError();
		if (_GLError != GL_NO_ERROR)
			DEBUG_PRINT("OpenGL Error: " + std::to_string(_GLError), LogLevel::WARNING);
#endif // SE_DEBUG
	}
}


void se::WindowManager::DestroyWindow()
{
	GetInstance()._DestroyWindow();
}

void se::WindowManager::_DestroyWindow()
{
	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window.Handler);
}
