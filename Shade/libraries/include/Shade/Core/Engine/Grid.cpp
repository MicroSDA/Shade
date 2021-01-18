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

	m_DrawCount = static_cast<GLuint>(m_Indices.size() * 4);

	m_VertexBuffer = se::VertexBuffer::Create<glm::fvec3, glm::uvec4>(
		{ {se::VertexBufferElementType::Float3, "Position"} },
		m_Vertices.data(), m_Vertices.size(),
		m_Indices.data(), m_Indices.size());
	glLineWidth(2.0f);
}

se::Grid::~Grid()
{
}

