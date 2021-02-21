#pragma once
#include <string>

class Util
{
public:
	static std::string GetNameFromPath(const std::string& filePath);
	static std::string GetPath(const std::string& filePath);
};

