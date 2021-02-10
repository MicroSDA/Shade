#pragma once
#include "Shade/Core/CoreAPI.h"

namespace se
{
	enum class SLCode
	{
		Event   = 1,
		Success = 10,
		InfoPrimary = 3,
		Error = 4,
		//Purpure = 5,
		Warning = 6,
		InfoSecondary = 8,
	};
	class SE_API Log
	{
	public:
		static void Print(const char* message, const se::SLCode& code);
	private:
		Log(const Log&) = delete;
		Log& operator= (const Log&) = delete;
		Log(const Log&&) = delete;
		Log& operator= (const Log&&) = delete;
		Log();
		~Log();

		static Log& GetInstance();
		void _Print(const char* message, const se::SLCode& code);
		const char* CurrentDateTime();

		void* m_hConsole;
	};
}



