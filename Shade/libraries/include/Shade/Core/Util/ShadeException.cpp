#include "stdafx.h"
#include "ShadeException.h"

se::ShadeException::ShadeException(const char* msg, const se::SECode& code) : std::exception(msg),
	m_Code(code)
{
}

se::ShadeException::~ShadeException()
{
}
