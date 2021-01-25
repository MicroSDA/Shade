#include "stdafx.h"
#include "VertexBuffer.h"


se::VertexBuffer::VertexBuffer():
	m_VAO(NULL), m_VBO(NULL), m_EBO(NULL) ,m_VBO_Size(0), m_EBO_Size(0)
{
}


se::VertexBuffer se::VertexBuffer::Create(const se::VertexBufferLayout& layout, const se::VertexBufferType& type, const uint32_t& verticesSize, const uint32_t& indicesSize)
{
	se::VertexBuffer _Buffer;
	_Buffer.m_Layout = layout;

	glGenVertexArrays(1, &_Buffer.m_VAO);
	glGenBuffers(1, &_Buffer.m_VBO);

	glBindVertexArray(_Buffer.m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _Buffer.m_VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, NULL, static_cast<GLint>(type));

	GLuint index = 0;
	for (auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.GeElementTypeCount(),
			element.ToOpenGLNativeType(),
			element.Normalized,
			layout.GetStride(),
			(const void*)(element.Offset));

		index++;
	}
	if (indicesSize)
	{
		glGenBuffers(1, &_Buffer.m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Buffer.m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, NULL, static_cast<GLint>(type));
	}

	glBindVertexArray(0);

	return std::move(_Buffer); 
}

void se::VertexBuffer::Reset()
{
	if (m_VAO)
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}
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
