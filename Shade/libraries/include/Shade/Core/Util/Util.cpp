#include "stdafx.h"
#include "Util.h"

std::string se::Util::GetNameFromPath(const std::string& filePath)
{
	std::size_t pos = filePath.find_last_of("/");
	std::string out = filePath;

	if (pos != std::string::npos)
	{
		out.erase(0, pos + 1);
		pos = out.find_last_of(".");
		if (pos != std::string::npos)
			out.erase(pos);
	}
	else
	{
		pos = out.find_last_of(".");
		if (pos != std::string::npos)
			out.erase(pos);
	}
	return out;
}

std::string se::Util::GetPath(const std::string& filePath)
{
	std::size_t pos = filePath.find_last_of("/");
	std::string out = filePath;

	if (pos != std::string::npos)
		out.erase(pos);
	return out;
}