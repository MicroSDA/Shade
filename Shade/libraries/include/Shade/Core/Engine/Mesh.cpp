#include "stdafx.h"
#include "Mesh.h"
#include <utility>
se::Mesh::Mesh(const std::string& fullClassName, const se::AssetData* data) : se::Asset(fullClassName, data), se::Drawable()
{
	m_DrawMode = se::DrawMode::TRIANGLES;
	m_AttribCount = 4; // DO NOT FORGET //

}

se::Mesh::~Mesh()
{
	/*glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);*/
}

void se::Mesh::SetVertices(std::vector<se::Vertex>& vertices)
{
	m_Vertices = std::move(vertices);
}

void se::Mesh::SetIndices(std::vector<unsigned int>& indices)
{
	m_Indices = std::move(indices);
	m_IndicesCount = m_Indices.size();
}

void se::Mesh::Load()
{
	// Nothing to do
}

void se::Mesh::Init()
{
	if (!m_IsInitialized)
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

		m_IsInitialized = true;
	}
	else
	{
		throw se::ShadeException(std::string("Asset has been already initialized'" + m_AssetData->_Path + "'").c_str(), se::SECode::Warning);
	}
	
}