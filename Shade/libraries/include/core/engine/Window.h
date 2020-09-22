#pragma once
#include <Definitions.h>
#include <SDL2/SDL.h>
#include <string>

namespace se
{
	typedef SDL_Window      WindowHandler;
	typedef SDL_WindowFlags WindowFlags;

	struct SE_API Window
	{
		std::string    Title = "Shade";
		unsigned int   Width = WINDOW_WIDTH;
		unsigned int   Height = WINDOW_HEIGHT;
		WindowHandler* Handler = nullptr;
		WindowFlags    WindowFlags = static_cast<se::WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		bool           IsClosed = false;
	};
}
