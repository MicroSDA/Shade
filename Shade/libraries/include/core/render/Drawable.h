#pragma once
#include <Definitions.h>
#include <glad/glad.h>

namespace se
{
	enum class SE_API DrawMode
	{
		TRINAGES = 4
	};
	class SE_API Drawable
	{
	public:
		Drawable();
		virtual ~Drawable();

		inline GLuint   GetVAO()          const { return m_VAO; }
		inline GLuint   GetAttribCount()  const { return m_AttribCount; }
		inline GLuint   GetIndicesCount() const { return m_IndicesCount; }
		inline DrawMode GetDrawMode()     const { return m_DrawMode; }
	protected:
		GLuint   m_VAO;
		GLuint   m_IndicesCount;
		GLuint   m_AttribCount;
		DrawMode m_DrawMode;
	};

}

