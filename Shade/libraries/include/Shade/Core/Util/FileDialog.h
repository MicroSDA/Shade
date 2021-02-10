#pragma once

#include "Shade/Core/CoreAPI.h"

namespace se
{
	class SE_API FileDialog
	{
	public:
		static std::string OpenFile(const char* filter);
	};

}

