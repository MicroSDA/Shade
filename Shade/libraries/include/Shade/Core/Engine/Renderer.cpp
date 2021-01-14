#include "stdafx.h"
#include "Renderer.h"
#include "Vendors/glad/glad.h"
#include "Shade/Core/Engine/WindowManager.h"

void se::Renderer::SetClearColor(const float& r, const float& g, const float& b, const float& a)
{
	se::WindowManager::Get().SetClearColor(r, g, b, a);
}

void se::Renderer::DrawIndexed(const se::Drawable& entity)
{
	
	glBindVertexArray(entity.GetVAO());

	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glEnableVertexAttribArray(attr);

		glDrawElements(static_cast<GLenum>(entity.GetDrawMode()), entity.GetIndicesCount(), GL_UNSIGNED_INT, NULL);

	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glDisableVertexAttribArray(attr);

	glBindVertexArray(0); // TODO Should be removed ?
}

void se::Renderer::DrawNotIndexed(const se::Drawable& entity, const GLuint& count)
{

	glBindVertexArray(entity.GetVAO());

	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glEnableVertexAttribArray(attr);

		glDrawArrays(static_cast<GLenum>(entity.GetDrawMode()), 0, (count == 0) ? entity.GetIndicesCount() : count);
	
	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glDisableVertexAttribArray(attr);

	glBindVertexArray(0); // TODO Should be removed?
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
