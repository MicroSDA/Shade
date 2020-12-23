#include "stdafx.h"
#include "Renderer.h"
#include "Vendors/glad/glad.h"

void se::Renderer::Draw(const se::Drawable& entity)
{
	//Bit textures and etc/.. Todo !!
	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glEnableVertexAttribArray(0);

	glBindVertexArray(entity.GetVAO());
	glDrawElements(static_cast<GLenum>(entity.GetDrawMode()), entity.GetIndicesCount(), GL_UNSIGNED_INT, 0);

	for (GLuint attr = 0; attr < entity.GetAttribCount(); attr++)
		glDisableVertexAttribArray(attr);
}
