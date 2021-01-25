#pragma once
#include "Shade/Core/Engine/VertexBuffer.h"

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
		inline const DrawMode&     GetDrawMode()     const { return  m_DrawMode; }
		inline const GLuint&       GetDrawCount()    const { return  m_DrawCount; }
		virtual const VertexBuffer& GetVertexBuffer() const = 0;
	protected:
		DrawMode         m_DrawMode;
		GLuint           m_DrawCount;
	private:
	};
}

