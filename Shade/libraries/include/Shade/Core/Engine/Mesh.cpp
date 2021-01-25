#include "stdafx.h"
#include "Mesh.h"
#include <utility>
se::Mesh::Mesh(const std::string& fullClassName, const se::AssetData* data) : se::Asset(fullClassName, data), se::Drawable()
{
	m_DrawMode = se::DrawMode::TRIANGLES;
}

se::Mesh::~Mesh()
{
}

void se::Mesh::SetVertices(std::vector<se::Vertex>& vertices)
{
	m_Vertices = std::move(vertices);
}

void se::Mesh::SetIndices(std::vector<unsigned int>& indices)
{
	m_Indices   = std::move(indices);
	m_DrawCount = static_cast<GLuint>(m_Indices.size());
}

void se::Mesh::Load()
{
	// Nothing to do
}

void se::Mesh::Init()
{
	if (!m_IsInitialized)
	{
		// Protect when mesh should be initialized outside of asset manager and data ins't seted yeat
		if (m_Indices.size() || m_Vertices.size())
		{
			m_VertexBuffer = se::VertexBuffer::Create(
				{ {se::VertexBufferElementType::Float3, "Position"},
				  {se::VertexBufferElementType::Float2, "TextureCoords"} ,
				  {se::VertexBufferElementType::Float3, "Normals"},
				  {se::VertexBufferElementType::Float3, "Tangents"} },
				se::VertexBufferType::Static,
				sizeof(se::Vertex) * m_Vertices.size(),
				sizeof(unsigned int) * m_Indices.size());

			m_VertexBuffer.SetVBO_Data(0, sizeof(se::Vertex)   * m_Vertices.size(), m_Vertices.data());
			m_VertexBuffer.SetEBO_Data(0, sizeof(unsigned int) * m_Indices.size(),  m_Indices.data());

			m_IsInitialized = true;
		}
		else
		{
			return;
		}
		
	}
	else
	{
		throw se::ShadeException(std::string("Asset has been already initialized'" + m_AssetData->_Path + "'").c_str(), se::SECode::Warning);
	}
}