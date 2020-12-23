#pragma once

#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"

namespace se
{
	class Drawable;
	class SE_API Renderer
	{
	public:
		static void Draw(const se::Drawable& entity);
	};
}
