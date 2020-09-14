#include "Log.h"

se::Log::Log()
{
}

se::Log::~Log()
{
}

se::Log& se::Log::GetInstance()
{
	static Log _Instatnce;
	return _Instatnce;
}

void se::Log::Print(const std::string& message, const LOG_LEVEL& level)
{
	GetInstance()._Print(message, level);
}

void se::Log::_Print(const std::string& message, const LOG_LEVEL& level)
{
	switch (level)
	{
	case LOG_LEVEL::INFO_SECONDARY:
		printf("\033[1;30m[%s] %s\n", CurrentDateTime().c_str(), message.c_str()); // grey
		break;
	case LOG_LEVEL::INFO_PRIMARY:
		printf("\033[1;36m[%s] %s\n", CurrentDateTime().c_str(), message.c_str()); // light blue
		break;
	case LOG_LEVEL::EVENT:
		printf("\033[1;34m[%s] %s\n", CurrentDateTime().c_str(), message.c_str()); // blue
		break;
	case LOG_LEVEL::SUCCESS:
		printf("\033[1;32m[%s] %s\n", CurrentDateTime().c_str(), message.c_str()); // green
		break;
	case LOG_LEVEL::WARNING:
		printf("\033[1;33m[%s] %s\n", CurrentDateTime().c_str(), message.c_str()); // yellow
		break;
	case LOG_LEVEL::ERROR:
		printf("\033[1;31m[%s] %s\n", CurrentDateTime().c_str(), message.c_str()); // red
		break;
	default:
		printf("\033[1;31m[%s] %s\n", CurrentDateTime().c_str(), "Undefined Log level!"); // red
		break;
	}
	
	//printf("\033[1;0m");
}

void se::Log::Save(const std::string& message)
{
	GetInstance()._Save(message);
}

void se::Log::_Save(const std::string& message)
{
	//Open logs file and save new log message
	m_LogFile.open(LOG_PATH, std::ofstream::app);
	std::string _Messgae(CurrentDateTime() + " [" + message + "]\n");
	m_LogFile.write(_Messgae.c_str(), sizeof(char) * _Messgae.size());
	m_LogFile.close();
}

const std::string se::Log::CurrentDateTime()
{
	time_t _Now = time(0);
	tm     _Time;
	char   _Buffer[80];

	localtime_s(&_Time, &_Now);
	strftime(_Buffer, sizeof(_Buffer), "%Y-%m-%d %X", &_Time);

	return _Buffer;
}
