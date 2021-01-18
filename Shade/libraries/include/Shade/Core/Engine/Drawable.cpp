#include "stdafx.h"
#include "Drawable.h"

se::Drawable::Drawable():
	m_DrawMode(DrawMode::TRIANGLES), m_DrawCount(0)
{
	
}

se::Drawable::~Drawable()
{
	/*if (!m_wasCopied)
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}
	else
	{
		m_wasCopied = false;
	}*/
}
