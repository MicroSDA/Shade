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
	glBindVertexArray(entity.GetVAO());

	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glEnableVertexAttribArray(attr);

	if (entity.GetIndicesCount())
	{
		glDrawElements(static_cast<GLenum>(entity.GetDrawMode()), entity.GetIndicesCount(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		Disable(GL_DEPTH_TEST);
			Enable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glDrawArrays(static_cast<GLenum>(entity.GetDrawMode()), 0, 4); // For Sprite only TODO resolve potential issue
			Disable(GL_BLEND);
		Enable(GL_DEPTH_TEST);
	}
		

	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glDisableVertexAttribArray(attr);

	glBindVertexArray(0);
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

inline void se::Renderer::BlendFunc(const GLenum& mode, const GLenum& mode2)
{
	glBlendFunc(mode, mode2);
}
