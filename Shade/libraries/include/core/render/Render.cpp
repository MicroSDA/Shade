#include "Render.h"
#include <glad/glad.h>

inline void  se::Render::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}
inline void se::Render::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void se::Render::DrawIndexed(const Drawable* element)
{
	
	/*for (GLuint attr = 0; attr < element->GetAttribCount(); attr++)
		glEnableVertexAttribArray(attr);
	glDrawElements(static_cast<GLenum>(element->GetDrawMode()), element->GetIndicesCount(), GL_UNSIGNED_INT, 0);
	for (GLuint attr = 0; attr < element->GetAttribCount(); attr++)
		glDisableVertexAttribArray(attr);*/

	
}

inline void se::Render::TestDraw()
{
	glDrawArrays(GL_POINTS, 0, 4);
}
