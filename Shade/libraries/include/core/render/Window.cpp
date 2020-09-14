#include "Window.h"

se::WindowManager::WindowManager()
    :m_Context(nullptr), m_IsClosed(false)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
#ifdef SE_DEBUG
        Log::Print(SDL_GetError(), LOG_LEVEL::ERROR);
#endif
        abort();
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GetCurrentDisplayMode(0, &m_DisplayMode);
  
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
    GetInstance()._CreateWindow(window);
}

void se::WindowManager::CreateWindow(Window&& window)
{
	GetInstance()._CreateWindow(std::forward<Window&>(window));
}

se::Window& se::WindowManager::GetWindow() 
{
    return GetInstance()._GetWindow();
}

void se::WindowManager::Update()
{
    GetInstance()._Update();
}

void se::WindowManager::_CreateWindow(Window& window)
{
    m_Window = window;

    m_Window.Handle = SDL_CreateWindow(
        m_Window.Title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_Window.Width,
        m_Window.Height,
        m_Window.WindowFlags
    );
   
    m_Context = SDL_GL_CreateContext(m_Window.Handle);

    SDL_GL_MakeCurrent(m_Window.Handle, m_Context);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
#ifdef SE_DEBUG
        Log::Print("Couldn't initialize glad", LOG_LEVEL::ERROR);
#endif
        abort();
    }
  
}

void se::WindowManager::_Close()
{
    m_IsClosed = true;
}

se::Window& se::WindowManager::_GetWindow()
{
    return m_Window;
}

void se::WindowManager::_Update()
{
    if (m_IsClosed)
    {
        SDL_GL_DeleteContext(m_Context);
        SDL_DestroyWindow(m_Window.Handle);
    }
    else
    {
        SDL_GL_SwapWindow(m_Window.Handle);

#ifdef SE_DEBUG
        GLenum _GLError = glGetError();
        if (_GLError != GL_NO_ERROR)
            Log::Print("OpenGL Error: " + std::to_string(_GLError), LOG_LEVEL::WARNING);
#endif // SE_DEBUG
    }
   
}
