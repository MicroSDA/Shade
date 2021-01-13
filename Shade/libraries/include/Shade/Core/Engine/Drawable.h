#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glad/glad.h"
#include "Shade/Core/Engine/Material.h"

namespace se
{
	enum class SE_API DrawMode
	{   
		POINTS         = 0,
		LINES          = 1,
		LINE_STRIP     = 2,
		LINE_LOOP      = 3,
		TRIANGLES      = 4,
		TRIANGLE_STRIP = 5,
		TRIANGLE_FAN   = 6,
	};
	class SE_API Drawable
	{
	public:
		Drawable();
		virtual ~Drawable();


		// Copy
		Drawable(const se::Drawable& other)
		{
			if (this != &other)
			{
				this->m_AttribCount   = other.m_AttribCount;
				this->m_DrawMode      = other.m_DrawMode;
				this->m_IndicesCount  = other.m_IndicesCount;
				this->m_VerticesCount = other.m_VerticesCount;
				this->m_VAO = other.m_VAO;
				this->m_VBO = other.m_VBO;
				this->m_EBO = other.m_EBO;

				m_wasCopied = true; // Then we can call delete vbo, ebo, vao in destructor
			}
		}
		Drawable& operator=(const Drawable& other)
		{
			if (this != &other)
			{
				this->m_AttribCount = other.m_AttribCount;
				this->m_DrawMode = other.m_DrawMode;
				this->m_IndicesCount = other.m_IndicesCount;
				this->m_VerticesCount = other.m_VerticesCount;
				this->m_VAO = other.m_VAO;
				this->m_VBO = other.m_VBO;
				this->m_EBO = other.m_EBO;

				m_wasCopied = true; // Then we can call delete vbo, ebo, vao in destructor
			}
			return *this;	
		}


		inline const GLuint&   GetVAO()          const { return  m_VAO; }
		inline const GLuint&   GetVBO()          const { return  m_VBO; }
		inline const GLuint&   GetEBO()          const { return  m_EBO; }
		inline const GLuint&   GetAttribCount()  const { return  m_AttribCount; }
		inline const GLuint&   GetIndicesCount() const { return  m_IndicesCount; }
		inline const GLuint&   GetVerticesCount() const { return m_VerticesCount; }
		inline const DrawMode& GetDrawMode()     const { return  m_DrawMode; }
		//inline const std::function<void()>& GetRenderPattern() const { return m_RenderPattern; }
	protected:
		GLuint       m_VAO, m_VBO, m_EBO;
		GLuint       m_IndicesCount;
		GLuint       m_VerticesCount;
		GLuint       m_AttribCount;
		DrawMode     m_DrawMode;
		//std::function<void()> m_RenderPattern;
	private:
		bool         m_wasCopied = false;
	};

}

