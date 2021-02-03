#pragma once
#include "Shade/Core/CoreAPI.h"
#include <SDL2/SDL.h>
namespace se
{
	class SE_API Timer
	{
	public:
		Timer();
		~Timer();

		int GetFps();
		void Update();
		operator double() const { return m_DeltaTime * 0.001; } // milliseconds
	private:
		double m_TimeLast, m_TimeNow, m_DeltaTime;
	};
}


