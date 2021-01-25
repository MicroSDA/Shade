#include "stdafx.h"
#include "Text.h"
#include "Shade/Core/Engine/Vertex.h"

se::Text::Text(): m_BufferSize(100) // for fisrt 100 characters
{
	se::AssetData s;
	m_Font = se::AssetPointer<se::Font>(new se::Font("s", &s));

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(se::Vertex2D) * m_BufferSize * 4, nullptr, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(se::Vertex2D), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(se::Vertex2D), (GLvoid*)offsetof(Vertex2D, m_TextureCoords));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_BufferSize * 6, nullptr, GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

se::Text::~Text()
{
}

void se::Text::SetText(const std::string& text)
{
	m_Text = text;

	if (text.size() > m_BufferSize)
	{
		m_BufferSize = m_BufferSize + 100;

		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(se::Vertex2D) * m_BufferSize * 4, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(se::Vertex2D), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(se::Vertex2D), (GLvoid*)offsetof(Vertex2D, m_TextureCoords));

		glBindVertexArray(0);
	}
	else if (text.size() < m_BufferSize - 100)
	{
		m_BufferSize = m_BufferSize - 100;

		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(se::Vertex2D) * m_BufferSize * 4, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(se::Vertex2D), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(se::Vertex2D), (GLvoid*)offsetof(Vertex2D, m_TextureCoords));

		glBindVertexArray(0);
	}


	std::vector<se::Vertex2D> Vertices;
	std::vector<GLuint>		  Indices;
	Vertices.reserve(text.size() * 6);
	float TileSize = 512.0f; // Temporary here
	float Offset   = 0.0f;
	size_t IndicesStride = 0;
	for (size_t i = 0; i < m_Text.size(); i++)
	{
		auto& CharData = m_Font->GetCharData(m_Text[i]);
		se::Vertex2D Vertex[4];
		// Position
		Vertex[0].m_Position = glm::vec2(-Offset, -CharData.Height - CharData.Yoffset);
		Vertex[1].m_Position = glm::vec2(-Offset, -CharData.Yoffset);
		Vertex[2].m_Position = glm::vec2(CharData.Width - Offset, -CharData.Yoffset);
		Vertex[3].m_Position = glm::vec2(CharData.Width - Offset, -CharData.Height - CharData.Yoffset);
		// TexCoords
		Vertex[0].m_TextureCoords = glm::vec2(CharData.Xpos / TileSize, (CharData.Ypos + CharData.Height) / TileSize);
		Vertex[1].m_TextureCoords = glm::vec2(CharData.Xpos / TileSize, CharData.Ypos / TileSize);
		Vertex[2].m_TextureCoords = glm::vec2((CharData.Xpos + CharData.Width) / TileSize, CharData.Ypos / TileSize);
		Vertex[3].m_TextureCoords = glm::vec2((CharData.Xpos + CharData.Width) / TileSize, (CharData.Ypos + CharData.Height) / TileSize);

		Vertices.push_back(Vertex[0]); Vertices.push_back(Vertex[1]); Vertices.push_back(Vertex[2]); Vertices.push_back(Vertex[3]);

		Offset = Offset - (CharData.Width + CharData.Xoffset);

		Indices.push_back(i + IndicesStride); // i
		Indices.push_back(i + IndicesStride + 1); // i + 1
		Indices.push_back(i + IndicesStride + 2); // i + 2
		Indices.push_back(i + IndicesStride + 2);//  i + 2
		Indices.push_back(i + IndicesStride); // i
		Indices.push_back(i + IndicesStride + 3); // i + 3

		IndicesStride += 3;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// If size of vertices isnt empty
	if(Vertices.size())
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(se::Vertex2D) * Vertices.size(), &Vertices[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_EBO);
	// If size of vertices isnt empty
	if (Indices.size())
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLuint) * Indices.size(), &Indices[0]);
}

const std::string& se::Text::GetText() const
{
	return m_Text;
}

void se::Text::Render()
{
	m_Font->GetAtlas()->Bind(0);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_Text.size() * 6, GL_UNSIGNED_INT, NULL);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}
