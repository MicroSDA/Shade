#include "stdafx.h"
#include "Model3D.h"
#include "Shade/Core/Util/Binarizer.h"
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Engine/AssetManager.h"
#include "Shade/Core/Engine/Components.h"

se::Model3D::Model3D(const std::string& fullClassName, const se::AssetData* data) :se::Asset(fullClassName, data)
{
}

se::Model3D::~Model3D()
{
	
}

void se::Model3D::Load()
{
	std::map<std::string, se::Material> _MaterialsMap;

	if (m_AssetData->_Dependency.size())
	{
		for (auto& _Asset : m_AssetData->_Dependency)
		{
			if (_Asset._Type == se::AssetDataType::Material)
			{
				std::ifstream _File;
				_File.open(_Asset._Path, std::ios::binary);
				if (!_File.is_open())
					throw se::ShadeException(std::string("Faild to open '" + _Asset._Path + "' file.").c_str(), se::SECode::Warning);
				// Set read position
				se::Binarizer::ReadAt(_File, m_AssetData->_Offset);
				//Header
				std::string _Header = se::Binarizer::ReadNext<std::string>(_File);
				_Header.pop_back(); // Remove \0
				if ("#ShadeMaterial" != _Header)
					throw se::ShadeException(std::string("Wrong header in '" + _Asset._Path + "' file.").c_str(), se::SECode::Warning);

				unsigned int _MaterialCount = se::Binarizer::ReadNext<unsigned int>(_File);
				if(!_MaterialCount)
					throw se::ShadeException(std::string("Material count = 0 in '" + _Asset._Path + "' file.").c_str(), se::SECode::Warning);

				for (unsigned int m = 0; m < _MaterialCount; m++)
				{
					se::Material _Material;
					glm::vec3    _Color;

					std::string _Name = se::Binarizer::ReadNext<std::string>(_File);
					_Name.pop_back(); // Remove \0
					
					_Color.r = se::Binarizer::ReadNext<float>(_File);
					_Color.g = se::Binarizer::ReadNext<float>(_File);
					_Color.b = se::Binarizer::ReadNext<float>(_File);
					_Material.SetAmbientColor(_Color);
					_Color.r = se::Binarizer::ReadNext<float>(_File);
					_Color.g = se::Binarizer::ReadNext<float>(_File);
					_Color.b = se::Binarizer::ReadNext<float>(_File);
					_Material.SetDiffuseColor(_Color);
					_Color.r = se::Binarizer::ReadNext<float>(_File);
					_Color.g = se::Binarizer::ReadNext<float>(_File);
					_Color.b = se::Binarizer::ReadNext<float>(_File);
					_Material.SetSpecularColor(_Color);
					_Color.r = se::Binarizer::ReadNext<float>(_File);
					_Color.g = se::Binarizer::ReadNext<float>(_File);
					_Color.b = se::Binarizer::ReadNext<float>(_File);
					_Material.SetTransparentMask(_Color);
					float _Value = se::Binarizer::ReadNext<float>(_File);
					_Material.SetShininess(_Value);
					_Value = se::Binarizer::ReadNext<float>(_File);
					_Material.SetShininessStrength(_Value);

					_MaterialsMap[_Name] = _Material;
				}
			}
		}
	}

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

	for (unsigned int m = 0; m < _MeshCount; m++)
	{
		se::Entity _MeshEntity = this->CreateEntity();

		std::string _MeshName = se::Binarizer::ReadNext<std::string>(_File);
		_MeshName.pop_back();

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
		
		// Creating otside of AssetManager
		auto _pMesh = se::AssetManager::Hold<se::Mesh>(m_FullClassName + "." + m_AssetData->_Dependency[m]._Name, false);
		_pMesh->SetVertices(_Vertices);
		_pMesh->SetIndices(_Indices);
		se::MeshComponent& _MeshComponent = _MeshEntity.AddComponent<se::MeshComponent>(_pMesh);
		_MeshEntity.AddComponent<se::MaterialComponent>(_MaterialsMap[_MeshName]);
		// Textures
		if (m_AssetData->_Dependency[m]._Dependency.size())
		{
			for (auto& _Asset : m_AssetData->_Dependency[m]._Dependency)
			{
				if (_Asset._Type == se::AssetDataType::Texture)
				{
					auto _TextureEntity = _MeshComponent.Mesh->CreateEntity();
					_TextureEntity.AddComponent<se::TextureComponent>(se::AssetManager::Hold<se::Texture>(m_FullClassName + "." + m_AssetData->_Dependency[m]._Name + "." + _Asset._Name, false));
				}
			}
		}

	
	}
	_File.close();
}

void se::Model3D::Init()
{
	if (!m_IsInitialized)
	{
		auto Meshes = this->GetEntities().view<se::MeshComponent>();

		for (auto& Mesh : Meshes)
		{
			Meshes.get<se::MeshComponent>(Mesh).Mesh->Init();
		}
		m_IsInitialized = true;
	}
	else
	{
		throw se::ShadeException(std::string("Asset has been already initialized'" + m_AssetData->_Path + "'").c_str(), se::SECode::Warning);
	}
	
}
