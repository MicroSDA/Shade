#include "stdafx.h"
#include "Renderer.h"
#include "Vendors/glad/glad.h"
#include "Shade/Core/Engine/WindowManager.h"

void se::Renderer::SetClearColor(const float& r, const float& g, const float& b, const float& a)
{
	se::WindowManager::Get().SetClearColor(r, g, b, a);
}

void se::Renderer::DrawIndexed(const se::Shader* shader, const se::Drawable& entity)
{
	
	glBindVertexArray(entity.GetVertexBuffer().GetVAO());
	glDrawElements(static_cast<GLenum>(entity.GetDrawMode()), entity.GetDrawCount(), GL_UNSIGNED_INT, GLM_NULLPTR);
}

void se::Renderer::DrawNotIndexed(const se::Shader* shader, const se::Drawable& entity, const GLuint& count)
{

	glBindVertexArray(entity.GetVertexBuffer().GetVAO());
	glDrawArrays(static_cast<GLenum>(entity.GetDrawMode()), 0, (count == 0) ? entity.GetDrawCount() : count);
}

inline void se::Renderer::Enable(const GLenum& capability)
{
	glEnable(capability);
}

inline void se::Renderer::Disable(const GLenum& capability)
{
	glDisable(capability);
}

inline void se::Renderer::CullFace(const GLenum& mode)
{
	glCullFace(mode);
}

inline void se::Renderer::BlendFunc(const GLenum& sfactor, const GLenum& dfactor)
{
	glBlendFunc(sfactor, dfactor);
}

inline void se::Renderer::PolygonMode(const GLenum& face, const GLenum& mode)
{
	glPolygonMode(face, mode);
}
