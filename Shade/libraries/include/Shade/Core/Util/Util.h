#pragma once
#include "Shade/Core/CoreAPI.h"

namespace se
{
	class SE_API Util
	{
	public:
		static std::string GetNameFromPath(const std::string& filePath);
		static std::string GetPath(const std::string& filePath);
	};
}