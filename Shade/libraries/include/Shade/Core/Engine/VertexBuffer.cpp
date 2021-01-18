#include "stdafx.h"
#include "VertexBuffer.h"


se::VertexBuffer::VertexBuffer():
	m_VAO(NULL), m_VBO(NULL), m_EBO(NULL)
{
}


se::VertexBuffer::~VertexBuffer()
{
	// If buffer was initialized, we can delete
	if (m_VAO)
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}
}
