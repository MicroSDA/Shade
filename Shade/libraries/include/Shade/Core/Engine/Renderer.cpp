#include "stdafx.h"
#include "Renderer.h"
#include "Vendors/glad/glad.h"
#include "Shade/Core/Engine/WindowManager.h"

void se::Renderer::SetClearColor(const float& r, const float& g, const float& b, const float& a)
{
	se::WindowManager::Get().SetClearColor(r, g, b, a);
}

void se::Renderer::Draw(const se::Drawable& entity)
{
	//Bit textures and etc/.. Todo !!
	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glEnableVertexAttribArray(attr);

	glBindVertexArray(entity.GetVAO());
	glDrawElements(static_cast<GLenum>(entity.GetDrawMode()), entity.GetIndicesCount(), GL_UNSIGNED_INT, 0);

	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glDisableVertexAttribArray(attr);
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