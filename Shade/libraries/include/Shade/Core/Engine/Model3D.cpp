#include "stdafx.h"
#include "Model3D.h"
#include "Shade/Core/Util/Binarizer.h"

se::Model3D::Model3D(const se::AssetData* data) :se::Asset(data)
{
}

se::Model3D::~Model3D()
{
}

void se::Model3D::Load()
{
	std::ifstream _File;
	_File.open(m_AssetData->_Path, std::ios::binary);
	if (!_File.is_open())
		throw se::ShadeException(std::string("Faild to open '" + m_AssetData->_Path + "' file.").c_str(), se::SECode::Warning);
	// Set read position
	se::Binarizer::ReadAt(_File, m_AssetData->_Offset);
	//Header
	std::string _Header = se::Binarizer::ReadNext<std::string>(_File);
	_Header.pop_back(); // Remove \0
	if ("#ShadeModel3D" != _Header)
		throw se::ShadeException(std::string("Wrong header in '" + m_AssetData->_Path + "' file.").c_str(), se::SECode::Warning);
    // Start to reading data
	unsigned int _MeshCount = se::Binarizer::ReadNext<unsigned int>(_File);
	if (!_MeshCount)
		throw se::ShadeException(std::string("Mesh count = 0 in '" + m_AssetData->_Path + "' file.").c_str(), se::SECode::Warning);

	m_Meshes.reserve(_MeshCount);
	for (unsigned int m = 0; m < _MeshCount; m++)
	{
		unsigned int _VertexCount = se::Binarizer::ReadNext<unsigned int>(_File);
		if (!_VertexCount)
			throw se::ShadeException(std::string("Vertex count = 0 in '" + m_AssetData->_Path + "' file.").c_str(), se::SECode::Warning);

		std::vector<Vertex> _Vertices;
		_Vertices.reserve(_VertexCount);
		for (unsigned int v = 0; v < _VertexCount; v++)
		{
			se::Vertex _Vertex;
			// Position
			_Vertex.m_Position.x = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Position.y = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Position.z = se::Binarizer::ReadNext<float>(_File);
			// Texture's coords
			_Vertex.m_TextureCoords.x = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_TextureCoords.y = se::Binarizer::ReadNext<float>(_File);
		    // Normals
			_Vertex.m_Normals.x = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Normals.y = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Normals.z = se::Binarizer::ReadNext<float>(_File);
			// Tangents
			_Vertex.m_Tangents.x = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Tangents.y = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Tangents.z = se::Binarizer::ReadNext<float>(_File);
			_Vertices.push_back(_Vertex);
		}
		// Indices
		unsigned int _IndicesCount = se::Binarizer::ReadNext<unsigned int>(_File);
		if (!_IndicesCount)
			throw se::ShadeException(std::string("Indices count = 0 in '" + m_AssetData->_Path + "' file.").c_str(), se::SECode::Warning);

		std::vector<unsigned int> _Indices;
		_Indices.reserve(_IndicesCount);
		for (unsigned int i = 0; i < _IndicesCount; i++)
			_Indices.push_back(se::Binarizer::ReadNext<unsigned int>(_File));

		m_Meshes.emplace_back(_Vertices, _Indices);
	}

	_File.close();
}
