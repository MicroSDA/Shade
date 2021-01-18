#pragma once

#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Mesh.h"
namespace se
{
	class Drawable;
	class SE_API Renderer
	{
	
	public:
		static void SetClearColor(const float& r, const float& g, const float& b, const float& a);
		static void DrawIndexed(const se::Shader* shader, const se::Drawable& entity);
		static void DrawNotIndexed(const se::Shader* shader, const se::Drawable& entity, const GLuint& count = 0);
		inline static void Enable(const GLenum& capability);
		inline static void Disable(const GLenum& capability);
		inline static void CullFace(const GLenum& mode);
		inline static void BlendFunc(const GLenum& sfactor, const GLenum& dfactor);
		inline static void PolygonMode(const GLenum& face, const GLenum& mode);
	};
}
