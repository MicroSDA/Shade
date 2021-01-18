#include "stdafx.h"
#include "Vertex.h"

se::Vertex::Vertex()
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_TextureCoords = glm::vec2(0.0f, 0.0f);
	m_Normals = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Tangents = glm::vec3(0.0f, 0.0f, 0.0f);
}

se::Vertex::Vertex(const glm::vec3& position,
	const glm::vec2& textureCoords,
	const glm::vec3& normals,
	const glm::vec3& tangents)
{
	m_Position = position;
	m_TextureCoords = textureCoords;
	m_Normals = normals;
	m_Tangents = tangents;
}

se::Vertex::Vertex(const float& positionX,
	const float& positionY,
	const float& positionZ,
	const float& textureCoordX,
	const float& textureCoordY,
	const float& normalX,
	const float& normalY,
	const float& normalZ,
	const float& tangentX,
	const float& tangentY,
	const float& tangentZ)
{
	m_Position.x = positionX;
	m_Position.y = positionY;
	m_Position.z = positionZ;

	m_TextureCoords.x = textureCoordX;
	m_TextureCoords.y = textureCoordY;

	m_Normals.x = normalX;
	m_Normals.y = normalY;
	m_Normals.z = normalZ;

	m_Tangents.x = tangentX;
	m_Tangents.y = tangentY;
	m_Tangents.z = tangentZ;
}

se::Vertex::~Vertex()
{
}

