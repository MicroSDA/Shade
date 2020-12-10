#include "Drawable.h"
#include <iostream>


se::Drawable::Drawable():
	m_VAO(NULL),
	m_AttribCount(1),
	m_IndicesCount(3),
	m_DrawMode(DrawMode::TRINAGES)
{

	//Only for test below
	GLfloat vertex[] = { 0.5f,  0.5f, 0.0f,  // top right
	                     0.5f, -0.5f, 0.0f,  // bottom right
	                    -0.5f, -0.5f, 0.0f
	                   };
	GLuint  indices[] = { 0, 1, 2 };

	glGenVertexArrays(1, &m_VAO);

	glGenBuffers(1, &m_VBO);

	glGenBuffers(1, &m_EBO);
	
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	
	glBindVertexArray(0);

	
}

se::Drawable::~Drawable()
{
}
