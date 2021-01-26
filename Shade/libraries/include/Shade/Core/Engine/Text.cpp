#include "stdafx.h"
#include "Text.h"
#include "Shade/Core/Engine/Vertex.h"

se::Text::Text() : se::Drawable(),
	m_BufferedCharCount(0)
{
	m_DrawMode = se::DrawMode::TRIANGLES;
}

se::Text::~Text()
{
}

void se::Text::SetText(const std::string& text)
{
	m_Text = text;
	if ((int)text.size() > m_BufferedCharCount) // 4 is num vertices 
	{
		m_BufferedCharCount = text.size() + 10;

		m_VertexBuffer = se::VertexBuffer::Create(
			{ {se::VertexBufferElementType::Float2, "Position"},
			  {se::VertexBufferElementType::Float2, "TextureCoords"} },
			se::VertexBufferType::Dynamic,
			sizeof(se::Vertex2D) * m_BufferedCharCount * 4, // allocate for 100 aditional charaters
			sizeof(unsigned int) * m_BufferedCharCount * 6); // allocate for 100 aditional charaters
	}
	else if ((int)text.size() < m_BufferedCharCount - 10 && text.size() > 0)
	{
		m_BufferedCharCount = m_BufferedCharCount - 10;

		m_VertexBuffer = se::VertexBuffer::Create(
			{ {se::VertexBufferElementType::Float2, "Position"},
			  {se::VertexBufferElementType::Float2, "TextureCoords"} },
			se::VertexBufferType::Dynamic,
			sizeof(se::Vertex2D) * m_BufferedCharCount * 4, // allocate for 100 aditional charaters
			sizeof(unsigned int) * m_BufferedCharCount * 6);  // allocate for 100 aditional charaters
	}

	if (m_Font != nullptr)
	{
		std::vector<se::Vertex2D> Vertices;
		std::vector<unsigned int> Indices;

		Vertices.reserve(text.size() * 4);
		Indices.reserve(text.size() * 6);


		float TileWidth = m_Font->GetFontData().m_TileWidth; 
		float TileHeight = m_Font->GetFontData().m_TileHeight;
		float Offset = 0.0f;
		size_t IndicesStride = 0;
		for (size_t i = 0; i < m_Text.size(); i++)
		{
			auto& CharData = m_Font->GetFontData().CharsData[m_Text[i]];
			se::Vertex2D Vertex[4];
			// Position
			Vertex[0].m_Position = glm::vec2(-Offset, -CharData.Height - CharData.Yoffset);
			Vertex[1].m_Position = glm::vec2(CharData.Width - Offset, -CharData.Height - CharData.Yoffset);
			Vertex[2].m_Position = glm::vec2(-Offset, -CharData.Yoffset);
			Vertex[3].m_Position = glm::vec2(CharData.Width - Offset, -CharData.Yoffset);
			// TexCoords
			Vertex[0].m_TextureCoords = glm::vec2(CharData.Xpos / TileWidth, (CharData.Ypos + CharData.Height) / TileHeight);
			Vertex[1].m_TextureCoords = glm::vec2((CharData.Xpos + CharData.Width) / TileWidth, (CharData.Ypos + CharData.Height) / TileHeight);
			Vertex[2].m_TextureCoords = glm::vec2(CharData.Xpos / TileWidth, CharData.Ypos / TileHeight);
			Vertex[3].m_TextureCoords = glm::vec2((CharData.Xpos + CharData.Width) / TileWidth, CharData.Ypos / TileHeight);

			Vertices.push_back(Vertex[0]); Vertices.push_back(Vertex[1]); Vertices.push_back(Vertex[2]); Vertices.push_back(Vertex[3]);

			Indices.push_back(i + IndicesStride); // i
			Indices.push_back(i + IndicesStride + 1); // i + 1
			Indices.push_back(i + IndicesStride + 2); // i + 2
			Indices.push_back(i + IndicesStride + 2);//  i + 2
			Indices.push_back(i + IndicesStride + 1); // i
			Indices.push_back(i + IndicesStride + 3); // i + 3

			IndicesStride += 3;

			Offset = Offset - (CharData.Width + CharData.Xoffset);
		}

		m_VertexBuffer.SetVBO_Data(0, sizeof(se::Vertex2D) * Vertices.size(), Vertices.data());
		m_VertexBuffer.SetEBO_Data(0, sizeof(unsigned int) * Indices.size(), Indices.data());

		m_DrawCount = Indices.size();
	}
}

const std::string& se::Text::GetText() const
{
	return m_Text;
}

void se::Text::SetFont(const se::AssetPointer<se::Font>& font)
{
	m_Font = font;
}

const se::AssetPointer<se::Font>& se::Text::GetFont() const
{
	return m_Font;
}

/*void se::Text::Render()
{
	m_Font->GetAtlas()->Bind(0);
	glBindVertexArray(m_VertexBuffer.GetVAO());
	glDrawElements(GL_TRIANGLES, m_Text.size() * 6, GL_UNSIGNED_INT, NULL);
}*/

const se::VertexBuffer& se::Text::GetVertexBuffer() const
{
	return m_VertexBuffer;
}

