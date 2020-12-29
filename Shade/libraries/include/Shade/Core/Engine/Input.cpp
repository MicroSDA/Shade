#include "stdafx.h"
#include "Input.h"

bool se::Input::IsKeyboardBPressed(const se::ScanCode& scancode)
{
    const Uint8* _State = SDL_GetKeyboardState(NULL);
    return _State[scancode];
}

bool se::Input::IsMouseBPressed(const int& button)
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
}

void se::Input::ShowCursor(const bool& toggle)
{
    SDL_ShowCursor(toggle);
}
