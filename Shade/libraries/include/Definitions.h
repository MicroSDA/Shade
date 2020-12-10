#pragma once
#include <SDL2/SDL.h>
#include <functional>

namespace se
{
    typedef SDL_Event     Event;
    typedef SDL_EventType EventType;
    typedef SDL_KeyCode   KeyCode;

    using EventCallback = std::function<bool(Event const&)>;

}

#define LOG_PATH "./logs/logs.txt"
#define ROAD_MAP_PATH "./RoadMap.bin"
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#ifdef SE_DEBUG
  #define DEBUG_PRINT(x,y) se::Log::Print(x,y)
#else 
  #define DEBUG_PRINT(x,y) 
#endif // SE_DEBUG  

#define DEBUG_SAVE(x) se::Log::Save(x)

#ifdef SE_WINDOWS
  #ifdef SE_DLL
    #define SE_API __declspec(dllexport)
  #else
    #define SE_API __declspec(dllimport)
  #endif
#else
  #error Undefined platforms, only Windows support!
#endif

