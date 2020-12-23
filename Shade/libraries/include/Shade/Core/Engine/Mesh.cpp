#include "stdafx.h"
#include "Mesh.h"

se::Mesh::Mesh(std::vector<se::Vertex>& vertices, std::vector<unsigned int>& indices):se::Drawable()
{
	m_Vertices = std::move(vertices);
	m_Indices  = std::move(indices);

	m_AttribCount = 1;
	m_IndicesCount = m_Indices.size();
	//Only for test below
	/*GLfloat vertex[] = { 0.5f,  0.5f, 0.0f,  // top right
						 0.5f, -0.5f, 0.0f,  // bottom right
						-0.5f, -0.5f, 0.0f
	};
	GLuint  indices[] = { 0, 1, 2 };*/

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(se::Vertex), &m_Vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(se::Vertex), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), &m_Indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);


}

se::Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

