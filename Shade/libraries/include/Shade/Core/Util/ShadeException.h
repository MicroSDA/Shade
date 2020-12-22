#pragma once
#include "Shade/Core/CoreAPI.h"

namespace se
{
	enum class SECode
	{
		Warning = 1,
		Error = -1
	};
	class SE_API ShadeException : public std::exception
	{
	public:
		ShadeException(const char* msg, const se::SECode& code);
		~ShadeException();
		const SECode& code() const { return m_Code; };
	private:
		SECode m_Code;
	};

}

