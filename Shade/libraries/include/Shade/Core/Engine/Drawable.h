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

		inline GLuint   GetVAO()          const { return m_VAO; }
		inline GLuint   GetAttribCount()  const { return m_AttribCount; }
		inline GLuint   GetIndicesCount() const { return m_IndicesCount; }
		inline DrawMode GetDrawMode()     const { return m_DrawMode; }
		inline const se::Material& GetMaterial() const { return m_Material; }
		virtual void    Init() = 0; // For opengl init
		//inline const std::function<void()>& GetRenderPattern() const { return m_RenderPattern; }
	protected:
		GLuint       m_VAO, m_VBO, m_EBO;
		GLuint       m_IndicesCount;
		GLuint       m_AttribCount;
		DrawMode     m_DrawMode;
		se::Material m_Material;
		//std::function<void()> m_RenderPattern;
	private:
		
	};

}

