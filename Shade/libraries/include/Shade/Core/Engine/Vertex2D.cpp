#include "stdafx.h"
#include "Vertex2D.h"

se::Vertex2D::Vertex2D()
{
	m_Position = glm::vec2(0.0f, 0.0f);
	m_TextureCoords = glm::vec2(0.0f, 0.0f);
}

se::Vertex2D::Vertex2D(const glm::vec2& position, const glm::vec2& textureCoords)
{
	m_Position = position;
	m_TextureCoords = textureCoords;
}

se::Vertex2D::Vertex2D(const float& positionX, const float& positionY,
	const float& textureCoordX,
	const float& textureCoordY)
{
	m_Position.x = positionX;
	m_Position.y = positionY;
	m_TextureCoords.x = textureCoordX;
	m_TextureCoords.y = textureCoordY;
}

se::Vertex2D::~Vertex2D()
{
}

