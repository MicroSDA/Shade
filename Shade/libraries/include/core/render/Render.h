#pragma once
#include <Definitions.h>
#include <glm/glm.hpp>
#include <core/render/Drawable.h>

namespace se
{
	class SE_API Render
	{
	public:
		inline static void SetClearColor(const glm::vec4& color);
		inline static void Clear();
		inline static void DrawIndexed(const Drawable* element);
		//inline static void
	};
}

