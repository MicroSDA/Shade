#pragma once
#pragma warning (disable:  4251) // DLL warnings
#pragma warning (disable:  4275) // DLL warnings

#ifdef SE_DEBUG
  #define SE_DEBUG_PRINT(x, y) se::Log::Print(x, y)
#else 
  #define SE_DEBUG_PRINT(x,y) 
#endif // SE_DEBUG  

 #ifdef SE_DLL
   #define SE_API __declspec(dllexport)
 #else
   #define SE_API __declspec(dllimport)
 #endif
