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

	m_VertexBuffer = se::VertexBuffer::Create(
		{ {se::VertexBufferElementType::Float3, "Position"} },
		se::VertexBufferType::Static,
		sizeof(glm::fvec3)* m_Vertices.size(),
		sizeof(glm::uvec4)* m_Indices.size());

	m_VertexBuffer.SetVBO_Data(0, sizeof(glm::fvec3) * m_Vertices.size(), m_Vertices.data());
	m_VertexBuffer.SetEBO_Data(0, sizeof(glm::uvec4) * m_Indices.size(), m_Indices.data());

	m_DrawCount = static_cast<GLuint>(m_Indices.size() * 4);

	glLineWidth(1.2f);
}

se::Grid::~Grid()
{
}

