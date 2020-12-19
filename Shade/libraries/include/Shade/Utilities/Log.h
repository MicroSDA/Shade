#pragma once
#include <Shade/Definitions.h>

#include <fstream>
#include <stdio.h>
#include <time.h>

namespace se
{
	enum class LogLevel
	{
		INFO_SECONDARY = 0,
		INFO_PRIMARY,
		EVENT,
		SUCCESS,
		WARNING,
		ERROR,

		COUNT
	};
	class SE_API Log
	{
	public:
		
		//Print message to the console
		static void Print(const std::string& message, const LogLevel& level);
		//Save logs into the logs file
		static void Save(const std::string& message);
	private:
		Log();
		~Log();
		//Delete copy and move constructor
		//Copy
		Log(const Log&) = delete;
		Log& operator= (const Log&) = delete;
		//Move
		Log(const Log&&) = delete;
		Log& operator= (const Log&&) = delete;
		//////////////////////////////////////
		static Log& GetInstance();

		void _Print(const std::string& message, const LogLevel& level);
		void _Save(const std::string& message);
		const std::string CurrentDateTime();

		std::ofstream m_LogFile;
	};

}

