#pragma once
#include "Shade/Core/CoreAPI.h"

namespace se
{
	class SE_API Timer
	{
	public:
		Timer();
		~Timer();

		void Update();
		operator float() const { return m_DeltaTime * 0.001; } // milliseconds
	private:
		double m_TimeLast, m_TimeNow, m_DeltaTime;
	};
}


