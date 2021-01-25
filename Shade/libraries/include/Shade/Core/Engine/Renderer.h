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
		static void DrawIndexed(const se::Drawable& entity);
		static void DrawNotIndexed(const se::Drawable& entity, const GLuint& count = 0);
		static void Enable(const GLenum& capability);
		static void Disable(const GLenum& capability);
		static void CullFace(const GLenum& mode);
		static void BlendFunc(const GLenum& sfactor, const GLenum& dfactor);
		static void PolygonMode(const GLenum& face, const GLenum& mode);
		static void BindTexture(const GLuint& id);
	};
}
