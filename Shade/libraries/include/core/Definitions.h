#pragma once

#define LOG_PATH "./logs/logs.txt"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#ifdef SE_DEBUG
  #define DEBUG_LOG(x,y) se::Log::Print(x,y)
#else 
  #define DEBUG_LOG(x,y) 
#endif // SE_DEBUG

#ifdef SE_WINDOWS
  #ifdef SE_DLL
    #define SE_API __declspec(dllexport)
  #else
    #define SE_API __declspec(dllimport)
  #endif
#else
  #error Undefined platforms, only Windows support!
#endif
