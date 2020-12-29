#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/SDL2/SDL.h"
#include "Shade/Core/Engine/WindowManager.h"
#include "Vendors/glm/glm.hpp"

namespace se
{
	typedef SDL_Scancode  ScanCode;

	class SE_API Input
	{
	public:
		static bool IsKeyboardBPressed(const se::ScanCode& scancode);
		static bool IsMouseBPressed(const int& button);
		static void ShowCursor(const bool& toggle);
		inline static const glm::ivec2& GetMousePosition()
		{ 
			static glm::ivec2 _Position;
			SDL_GetMouseState(&_Position.x, &_Position.y);
			return _Position;
		};
		inline static void SetMousePosition(const int& x, const int& y)
		{
			SDL_WarpMouseInWindow(se::WindowManager::GetWindow().Handler, x, y);
		}
	};
	
}

