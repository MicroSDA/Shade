#include "stdafx.h"
#include "Mesh.h"

se::Mesh::Mesh(std::vector<se::Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<se::Texture*>& textures):se::Drawable()
{
	m_Vertices  = std::move(vertices); // std::move to keep from distructor calling !
	m_Indices   = std::move(indices);
	m_Textures  = std::move(textures);

	m_IndicesCount = m_Indices.size();
	m_AttribCount = 3; // DO NOT FORGET //
}

se::Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void se::Mesh::Init()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(se::Vertex), &m_Vertices[0], GL_STATIC_DRAW);
	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(se::Vertex), (GLvoid*)0);
	// Vertex Texture Coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(se::Vertex), (GLvoid*)offsetof(se::Vertex, m_TextureCoords));
	// Vertex Normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(se::Vertex), (GLvoid*)offsetof(se::Vertex, m_Normals));
	// Vertex Tangents
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(se::Vertex), (GLvoid*)offsetof(se::Vertex, m_Tangents));

	// Vertex indices
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), &m_Indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0); // just for save
}