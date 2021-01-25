#include "stdafx.h"
#include "Timer.h"
#include "Vendors/SDL2/SDL.h"

int se::Timer::GetFps()
{
	
	return 0;
}

void se::Timer::Update()
{
	m_TimeLast = m_TimeNow;
	m_TimeNow = SDL_GetPerformanceCounter();
	m_DeltaTime = (double)((m_TimeNow - m_TimeLast) * 1000 / (double)SDL_GetPerformanceFrequency());
}


se::Timer::Timer():
	m_TimeNow(SDL_GetPerformanceCounter()), m_TimeLast(0.0f), m_DeltaTime(0.0f)
{
	SDL_WasInit(SDL_INIT_TIMER);
}

se::Timer::~Timer()
{
}

