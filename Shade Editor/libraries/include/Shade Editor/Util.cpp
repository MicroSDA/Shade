#include "Util.h"

std::string Util::GetNameFromPath(const std::string& filePath)
{
    return std::string();
}

std::string Util::GetPath(const std::string& filePath)
{
	std::size_t _Pos = filePath.find_last_of("/");
	std::string _Out = filePath;

	if (_Pos != std::string::npos)
	{
		_Out.erase(_Pos);
		return _Out;
	}
	else
	{
		return _Out;
	}
}
