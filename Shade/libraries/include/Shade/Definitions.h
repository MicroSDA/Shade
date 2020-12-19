#pragma once
#pragma warning (disable:  4251)

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

// Remove if static link
#ifdef SE_WINDOWS
  #ifdef SE_DLL
    #define SE_API __declspec(dllexport)
  #else
    #define SE_API __declspec(dllimport)
  #endif
#else
  #error Undefined plat forms, only Windows support!
#endif

