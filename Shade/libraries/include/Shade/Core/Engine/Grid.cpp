#include "stdafx.h"
#include "Grid.h"


se::Grid::Grid(const float& width, const float& height, const int& density)
{
	m_DrawMode = se::DrawMode::LINES;
	
	for (int j = 0; j <= density; ++ j ) {
		for (int i = 0; i <= density; ++i) {
			float x = (float)i / (float)density;
			float y = 0;
			float z = (float)j / (float)density;
			m_Vertices.push_back(glm::vec3((x * width)- width / 2, 0.0f, (z * height)- height/2 ));
		}
	}

	for (int j = 0; j < density; ++j) {
		for (int i = 0; i < density; ++i) {

			int row1 = j * (density + 1);
			int row2 = (j + 1) * (density + 1);

			m_Indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
			m_Indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));

		}
	}

	m_IndicesCount = m_Indices.size() * 4;
	m_AttribCount  = 1;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::fvec3), &m_Vertices[0], GL_STATIC_DRAW);
	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	// Vertex indices
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(glm::uvec4), &m_Indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0); // just for save
}

se::Grid::~Grid()
{

}
