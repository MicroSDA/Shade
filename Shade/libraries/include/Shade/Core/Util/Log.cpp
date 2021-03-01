#include "stdafx.h"
#include "Log.h"

void se::Log::Print(const std::string& message, const se::SLCode& code)
{
	GetInstance()._Print(message.c_str(), code);
}

void se::Log::Print(const char* message, const se::SLCode& code)
{
	GetInstance()._Print(message, code);
}

se::Log::Log()
{
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

se::Log::~Log()
{
}

se::Log& se::Log::GetInstance()
{
	static Log _Instatnce;
	return _Instatnce;
}

void se::Log::_Print(const char* message, const se::SLCode& code)
{
	SetConsoleTextAttribute(m_hConsole, (WORD)code);
	std::cerr <<"[" << CurrentDateTime() << "]: "<< message << std::endl;
	SetConsoleTextAttribute(m_hConsole, 7);
}

const char* se::Log::CurrentDateTime()
{
	time_t      _Now = time(0);
	tm          _Time;
	static char _Buffer[80];

	localtime_s(&_Time, &_Now);
	strftime(_Buffer, sizeof(_Buffer), "%Y-%m-%d %X", &_Time);

	return _Buffer;
}
