#pragma once

#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"

namespace se
{
	class Drawable;
	class SE_API Renderer
	{
	
	public:
		static void SetClearColor(const float& r, const float& g, const float& b, const float& a);
		static void Draw(const se::Drawable& entity);
		inline static void Enable(const GLenum& capability);
		inline static void Disable(const GLenum& capability);
		inline static void CullFace(const GLenum& mode);
	};
}
