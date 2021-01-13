#include "stdafx.h"
#include "Drawable.h"

se::Drawable::Drawable():
	m_VAO(NULL), m_VBO(NULL), m_EBO(NULL),
	m_AttribCount(NULL),
	m_IndicesCount(NULL),
	m_VerticesCount(NULL),
	m_DrawMode(DrawMode::TRIANGLES)
{
	
}

se::Drawable::~Drawable()
{
	if (!m_wasCopied)
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}
	else
	{
		m_wasCopied = false;
	}
}
