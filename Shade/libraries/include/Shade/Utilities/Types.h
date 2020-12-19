#pragma once
#include <Shade/Vendors/SDL2/SDL.h>
#include <functional>

namespace se
{
    typedef SDL_Event     Event;
    typedef SDL_EventType EventType;
    typedef SDL_KeyCode   KeyCode;

    using EventCallback = std::function<bool(Event const&)>;
}