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
	{
		std::cout << "Error open model file\n";
		exit(-1);
	}

	_File.seekg(m_AssetData->_Offset);
	std::string _Header = se::Binarizer::ReadNext<std::string>(_File);
	_Header.pop_back(); // Remove \0
	if ("#ShadeModel3D" != _Header)
	{
		std::cout << "Wrong model's header\n";
		exit(-1);
	}


	unsigned int _MeshCount = se::Binarizer::ReadNext<unsigned int>(_File);
	if (!_MeshCount)
	{
		std::cout << "Zero meshes!\n";
		exit(-1);
	}


	m_Meshes.reserve(_MeshCount);

	for (unsigned int m = 0; m < _MeshCount; m++)
	{
		unsigned int _VertexCount = se::Binarizer::ReadNext<unsigned int>(_File);
		if (!_VertexCount)
		{
			std::cout << "Zero vertices!\n";
			exit(-1);
		}

		std::vector<Vertex> _Vertices;
		_Vertices.reserve(_VertexCount);

		for (unsigned int v = 0; v < _VertexCount; v++)
		{
			se::Vertex _Vertex;
			_Vertex.m_Position.x = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Position.y = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Position.z = se::Binarizer::ReadNext<float>(_File);

			_Vertex.m_TextureCoords.x = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_TextureCoords.y = se::Binarizer::ReadNext<float>(_File);
		
			_Vertex.m_Normals.x = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Normals.y = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Normals.z = se::Binarizer::ReadNext<float>(_File);

			_Vertex.m_Tangents.x = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Tangents.y = se::Binarizer::ReadNext<float>(_File);
			_Vertex.m_Tangents.z = se::Binarizer::ReadNext<float>(_File);
			_Vertices.push_back(_Vertex);
		}
		unsigned int _IndicesCount = se::Binarizer::ReadNext<unsigned int>(_File);
		if (!_IndicesCount)
		{
			std::cout << "Zero indices!\n";
			exit(-1);
		}

		std::vector<unsigned int> _Indices;
		_Indices.reserve(_IndicesCount);
		for (unsigned int i = 0; i < _IndicesCount; i++)
		{
			_Indices.push_back(se::Binarizer::ReadNext<unsigned int>(_File));
		}
		
		m_Meshes.emplace_back(_Vertices, _Indices);
	}

	_File.close();
	//m_Meshes.emplace_back();
}
