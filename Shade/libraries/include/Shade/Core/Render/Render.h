#pragma once
#include <Shade/Definitions.h>
#include <Shade/Core/Render/Drawable.h>
#include <Shade/Vendors/glm/glm.hpp>

namespace se
{
	class SE_API Render
	{
	public:
		inline static void SetClearColor(const glm::vec4& color);
		inline static void Clear();
		inline static void DrawIndexed(const Drawable* element);
		inline static void TestDraw();
		//inline static void
	};
}

