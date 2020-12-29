#include "stdafx.h"
#include "Serializer.h"
#include <Shade/Core/Util/ShadeException.h>

Serializer::Serializer()
{
}

Serializer::~Serializer()
{
}

bool Serializer::SerializeModel(const std::string& filePath)
{
	m_FilePath = filePath;
	Assimp::Importer importer;
	const aiScene* m_pScene = importer.ReadFile(filePath,
		aiProcess_FlipUVs |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_CalcTangentSpace |
		aiProcess_FixInfacingNormals |
		aiProcess_GenSmoothNormals
	);
	// If the import failed, report it
	if (!m_pScene)
	{
		std::cerr << importer.GetErrorString() << std::endl;
		return false;
	}
	else {

		processNode(m_pScene->mRootNode, m_pScene);
	}

	std::string _Name = GetNameFromPath(filePath) + ".bin";
	std::ofstream _File;
	_File.open("./resources/models/" + _Name, std::ios::binary);
	if (_File.is_open())
	{
		//Header
		se::Binarizer::WriteNext<std::string>(_File, "#ShadeModel3D");
		//Mesh count
		se::Binarizer::WriteNext<unsigned int>(_File, m_Meshes.size());

		for (auto& mesh : m_Meshes)
		{
			//Vertex count 
			se::Binarizer::WriteNext<unsigned int>(_File, mesh.vertices.size());

			for (auto& vertex : mesh.vertices)
			{
				se::Binarizer::WriteNext<float>(_File, vertex.m_Position.x);
				se::Binarizer::WriteNext<float>(_File, vertex.m_Position.y);
				se::Binarizer::WriteNext<float>(_File, vertex.m_Position.z);

				se::Binarizer::WriteNext<float>(_File, vertex.m_TextureCoords.x);
				se::Binarizer::WriteNext<float>(_File, vertex.m_TextureCoords.y);

				se::Binarizer::WriteNext<float>(_File, vertex.m_Normals.x);
				se::Binarizer::WriteNext<float>(_File, vertex.m_Normals.y);
				se::Binarizer::WriteNext<float>(_File, vertex.m_Normals.z);

				se::Binarizer::WriteNext<float>(_File, vertex.m_Tangents.x);
				se::Binarizer::WriteNext<float>(_File, vertex.m_Tangents.y);
				se::Binarizer::WriteNext<float>(_File, vertex.m_Tangents.z);
			}
			se::Binarizer::WriteNext<unsigned int>(_File, mesh.indices.size());
			for (auto& index : mesh.indices)
			{
				se::Binarizer::WriteNext<unsigned int>(_File, index);
			}
		}

		_File.close();
	}
	else
	{
		throw se::ShadeException(std::string("Failed to open model '" + _Name + "' !").c_str(), se::SECode::Warning);
	}

	return true;
}

bool Serializer::SerializeShader(const std::vector<Shader>& shaders, se::AssetData* data)
{
	std::vector<std::string> _ShadersCource;
	_ShadersCource.resize(shaders.size());

	std::regex  include(".*#include[ ]*[\"<](.*)[\">].*");
	std::smatch includeMatch;
	
	for (short s = 0 ; s< shaders.size(); s++)	
	{
		std::ifstream _Read;
		_Read.open(shaders[s].path, std::ios::binary);
		if (!_Read.is_open())
			throw se::ShadeException(std::string("Failed to open shader file '" + shaders[s].path + "' !").c_str(), se::SECode::Warning);

		_ShadersCource[s] += shaders[s].type;
		std::string line;
		while (_Read.good())
		{
			std::getline(_Read, line);
			
			if (std::regex_search(line, includeMatch, include))
			{
				std::ifstream _Include;
				_Include.open(includeMatch[1], std::ios::binary);
				if (!_Include.is_open())
					throw se::ShadeException(std::string("Failed to open sahder include file '" + shaders[s].path + "' !").c_str(), se::SECode::Warning);
				
				std::string includeLine;
				while (_Include.good())
				{
					std::getline(_Include, includeLine);
					_ShadersCource[s] += "\n" + includeLine;
				}

				std::getline(_Read, line); // Next line to skip #include 
			}

			_ShadersCource[s] += "\n" + line;
		}

		_ShadersCource[s] += "\n#end";
		_Read.close();
	}

	std::ofstream _Write;
	_Write.open("./resources/shaders/shaders.bin", std::ios::binary);
	if (_Write.is_open())
	{
		_Write.write("#BasicModel\n", 12);
		for (short s = 0; s < shaders.size(); s++)
		{
			_Write.write(_ShadersCource[s].c_str(), _ShadersCource[s].size());
			_Write.write("\n", 1);
		}

		_Write.write("#---", 4);
		_Write.close();
	}
	else
	{
		throw se::ShadeException(std::string("Failed to save sahder file './resources/shaders/shaders.bin' !").c_str(), se::SECode::Warning);
	}
	
	return false;
}

bool Serializer::SerializeImage(const std::string& filePath)
{
	int _Width , _Height, _Channels;
	unsigned char* _Data = stbi_load(filePath.c_str(), &_Width, &_Height, &_Channels, STBI_rgb_alpha);
	if (_Data)
	{
		std::ofstream _File;
		_File.open("./resources/textures/" + GetNameFromPath(filePath) + ".bin", std::ios::binary);
		if (_File.is_open())
		{
			se::Binarizer::WriteNext<std::string>(_File, "#ShadeImage");
			se::Binarizer::WriteNext<int>(_File, _Width);
			se::Binarizer::WriteNext<int>(_File, _Height);
			se::Binarizer::WriteNext<int>(_File, _Channels);
			unsigned int _Size = (_Channels * _Width * _Height);
			se::Binarizer::WriteNext<unsigned int>(_File, _Size);
			_File.write(reinterpret_cast<char*>(_Data), _Size);
			_File.close();
		}
		else
		{
			throw se::ShadeException(std::string("Failed to save image '" + filePath + "' !").c_str(), se::SECode::Warning);
		}

		stbi_image_free(_Data);
	}
	else
	{
		throw se::ShadeException(std::string("Failed to open source image '" + filePath + "' !").c_str(), se::SECode::Warning);
	}
	
	return true;
}

void Serializer::processNode(const aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(processMesh(mesh, scene, i));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}

}

Model Serializer::processMesh(aiMesh* mesh, const aiScene* scene, unsigned int id)
{
	std::vector<se::Vertex> _Vertices;
	std::vector<unsigned int> _Indices;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		se::Vertex _Vertex;
		_Vertex.m_Position.x = mesh->mVertices[i].x;
		_Vertex.m_Position.y = mesh->mVertices[i].y;
		_Vertex.m_Position.z = mesh->mVertices[i].z;

		if (mesh->HasNormals()) 
		{
			_Vertex.m_Normals.x = mesh->mNormals[i].x;
			_Vertex.m_Normals.y = mesh->mNormals[i].y;
			_Vertex.m_Normals.z = mesh->mNormals[i].z;
			if (mesh->HasTangentsAndBitangents())
			{
				_Vertex.m_Tangents.x = mesh->mTangents[i].x;
				_Vertex.m_Tangents.y = mesh->mTangents[i].y;
				_Vertex.m_Tangents.z = mesh->mTangents[i].z;
			}
			else
			{
				//TODO
			}
		}
		else {

			//TODO: if noramls doesnt exist
		}

		if (mesh->HasTextureCoords(0)) 
		{
			_Vertex.m_TextureCoords.x = mesh->mTextureCoords[0][i].x;
			_Vertex.m_TextureCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else 
		{
			//TODO: if textCoors doesnt exist
		}

		_Vertices.push_back(_Vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace& face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			_Indices.push_back(face.mIndices[j]);
		}
	}
	Model _Model;
	_Model.name = mesh->mName.data;
	_Model.vertices = _Vertices;
	_Model.indices = _Indices;
	return _Model;
}

std::string Serializer::GetNameFromPath(const std::string& filePath)
{
	std::size_t _Pos = filePath.find_last_of("/");
	std::string _Out = filePath;

	if (_Pos != std::string::npos)
	{
		_Out.erase(0, _Pos + 1);
		_Pos = _Out.find_last_of(".");
		if (_Pos != std::string::npos)
		{
			_Out.erase(_Pos);
			return _Out;
		}
		else
		{
			throw se::ShadeException(std::string("Faild to get name from path :'" + filePath + "'").c_str(), se::SECode::Warning);
		}
	}
	else
	{
		_Pos = _Out.find_last_of(".");
		if (_Pos != std::string::npos)
		{
			_Out.erase(_Pos);
			return _Out;
		}
		else
		{
			throw se::ShadeException(std::string("Faild to get name from path :'" + filePath + "'").c_str(), se::SECode::Warning);
		}
	}
}
