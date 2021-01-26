#include "stdafx.h"
#include "Serrializer.h"
#include <Shade/Core/Util/ShadeException.h>


std::string Serrializer::GetNameFromPath(const std::string& filePath)
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

std::string Serrializer::GetPath(const std::string& filePath)
{
	std::size_t _Pos = filePath.find_last_of("/");
	std::string _Out = filePath;

	if (_Pos != std::string::npos)
	{
		_Out.erase(_Pos);
		return _Out;
	}
	else
	{
		throw se::ShadeException(std::string("Faild to get path from :'" + filePath + "'").c_str(), se::SECode::Warning);
	}
}

void Serrializer::Serrialize3DModel(const std::string& filePath, se::AssetData* const& assetData, const bool& withDeps)
{
	Assimp::Importer importer;
	const aiScene* m_pScene = importer.ReadFile(filePath,
		aiProcess_FlipUVs |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_CalcTangentSpace |
		aiProcess_FixInfacingNormals |
		aiProcess_GenSmoothNormals
	);
	if (!m_pScene)
	{
		throw se::ShadeException(importer.GetErrorString(), se::SECode::Warning);
		return;
	}
	else 
	{
		assetData->_Type = se::AssetDataType::Model3D;
		std::string _Path;
		if (withDeps)
		{
			_Path = GetPath(filePath);
		}

		std::vector<AssimpMesh> _Meshes = ProcessModel3DNode(_Path, m_pScene->mRootNode, m_pScene, *assetData);
		assetData->_Path += assetData->_Name + ".bin";

		std::ofstream _File;
		_File.open(assetData->_Path, std::ios::binary);
		if (_File.is_open())
		{
			//Header
			se::Binarizer::WriteNext<std::string>(_File, "#ShadeModel3D");
			//Mesh count
			se::Binarizer::WriteNext<unsigned int>(_File, _Meshes.size());

			for (auto& mesh : _Meshes)
			{
				//Name
				se::Binarizer::WriteNext<std::string>(_File, mesh._Name);
				//Vertex count 
				se::Binarizer::WriteNext<unsigned int>(_File, mesh._Vertices.size());
			

				for (auto& vertex : mesh._Vertices)
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
				se::Binarizer::WriteNext<unsigned int>(_File, mesh._Indices.size());
				for (auto& index : mesh._Indices)
				{
					se::Binarizer::WriteNext<unsigned int>(_File, index);
				}
			}

			_File.close();
		}
		else
		{
			throw se::ShadeException(std::string("Failed to open model '" + assetData->_Path + "' !").c_str(), se::SECode::Warning);
		}

		std::vector<se::Material> _Materials;
		for (auto& _Mesh : _Meshes)
		{
			if (_Mesh._HasMaterial)
			{
				_Materials.push_back(_Mesh._Material);
			}
		}
		if (_Materials.size())
		{
			se::AssetData _Material;
			_Material._Name = "Material";
			_Material._Type = se::AssetDataType::Material;
			_Material._Path = GetPath(assetData->_Path) + "/material.bin";
			SerrializeMaterial(_Material._Path, _Materials, assetData);
			assetData->_Dependency.push_back(_Material);
		}
		

		_Meshes.clear();

	}
}

void Serrializer::SerrializeTexture(const std::string& filePath, se::AssetData* const& assetData, const bool& withDeps)
{
	int _Width, _Height, _Channels;
	unsigned char* _Data = stbi_load(filePath.c_str(), &_Width, &_Height, &_Channels, STBI_rgb_alpha);
	if (_Data)
	{
		std::ofstream _File;
		_File.open(assetData->_Path, std::ios::binary);
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
			throw se::ShadeException(std::string("Failed to save image '" + assetData->_Path + "' !").c_str(), se::SECode::Warning);
		}

		stbi_image_free(_Data);
	}
	else
	{
		throw se::ShadeException(std::string("Failed to open source image '" + filePath + "' !").c_str(), se::SECode::Warning);
	}
}

void Serrializer::SerrializeMaterial(const std::string& filePath, const std::vector<se::Material>& materials, se::AssetData* const& assetData)
{
	std::ofstream _File;
	_File.open(filePath, std::ios::binary);
	if (_File.is_open())
	{
		se::Binarizer::WriteNext<std::string>(_File,  "#ShadeMaterial");
		se::Binarizer::WriteNext<unsigned int>(_File,  materials.size());

		for (auto& _Material : materials)
		{
			se::Binarizer::WriteNext<std::string>(_File, _Material.GetName());

			glm::vec3 _Color = _Material.GetAmbientColor();
			se::Binarizer::WriteNext<float>(_File, _Color.r);
			se::Binarizer::WriteNext<float>(_File, _Color.g);
			se::Binarizer::WriteNext<float>(_File, _Color.b);
			_Color = _Material.GetDiffuseColor();
			se::Binarizer::WriteNext<float>(_File, _Color.r);
			se::Binarizer::WriteNext<float>(_File, _Color.g);
			se::Binarizer::WriteNext<float>(_File, _Color.b);
			_Color = _Material.GetSpecularColor();
			se::Binarizer::WriteNext<float>(_File, _Color.r);
			se::Binarizer::WriteNext<float>(_File, _Color.g);
			se::Binarizer::WriteNext<float>(_File, _Color.b);
			_Color = _Material.GetTransparentMask();
			se::Binarizer::WriteNext<float>(_File, _Color.r);
			se::Binarizer::WriteNext<float>(_File, _Color.g);
			se::Binarizer::WriteNext<float>(_File, _Color.b);

			se::Binarizer::WriteNext<float>(_File, (_Material.GetShinines() <= 0) ? 10 : _Material.GetShinines());
			se::Binarizer::WriteNext<float>(_File, (_Material.GetShininesStrength() <= 0) ? 10 : _Material.GetShininesStrength());
		}

		_File.close();
	}
	else
	{
		throw se::ShadeException(std::string("Failed to open material '" + filePath + "' !").c_str(), se::SECode::Warning);
	}
	

}

void Serrializer::SerrializeShader(const std::vector<ShaderMeta>& shaders, se::AssetData* const& assetData)
{
	std::vector<std::string> _ShadersSource;
	_ShadersSource.resize(shaders.size());
	std::regex  include(".*#include[ ]*[\"<](.*)[\">].*");
	std::smatch includeMatch;

	for (short s = 0; s < shaders.size(); s++)
	{
		std::ifstream _Read;
		_Read.open(shaders[s]._Path, std::ios::binary);
		if (!_Read.is_open())
			throw se::ShadeException(std::string("Failed to open shader file '" + shaders[s]._Path + "' !").c_str(), se::SECode::Warning);

		_ShadersSource[s] += shaders[s]._Type;
		std::string line;
		while (_Read.good())
		{
			std::getline(_Read, line);

			if (std::regex_search(line, includeMatch, include))
			{
				_ShadersSource[s] += ProcessShaderInclude(includeMatch[1], include);
				continue;
			}

			_ShadersSource[s] += "\n" + line;
		}

		_ShadersSource[s] += "\n#end";
		_Read.close();
	}

	std::ofstream _Write;
	_Write.open(assetData->_Path + assetData->_Name + ".bin", std::ios::binary);
	if (_Write.is_open())
	{
		std::string _Name = "#" + assetData->_Name + "\n";
		_Write.write(_Name.c_str(), _Name.size());
		for (short s = 0; s < shaders.size(); s++)
		{
			_Write.write(_ShadersSource[s].c_str(), _ShadersSource[s].size());
			_Write.write("\n", 1);
		}

		_Write.write("#---", 4);
		_Write.close();

		assetData->_Path = assetData->_Path + assetData->_Name + ".bin";
	}
	else
	{
		throw se::ShadeException(std::string("Failed to save sahder file '"+ assetData->_Path + assetData->_Name + ".bin" +"'").c_str(), se::SECode::Warning);
	}
}

void Serrializer::SerrializeFont(const std::string& filePath, se::AssetData* const& assetData, const bool& withDeps)
{
	struct CharData
	{
		int AsciiCode = -1;
		float Xpos = 0, Ypos = 0;
		float Width = 0.0f, Height = 0.0f;
		float Xoffset = 0.0f, Yoffset = 0.0f;
		float Xadvance = 0.0f;
	};
	struct FontData
	{
		std::unordered_map<char, CharData> CharsData;
		float TileWidth = 0.0f, TileHeight = 0.0f;
		int   Count = 0;
		std::string AtlasPath;
	};

	std::ifstream _File;
	_File.open(filePath);
	if (_File.is_open())
	{
		std::string _Node;
		FontData _FontData;
		while (!_File.eof())
		{
			_File >> _Node;

			if (_Node.find("count") != _Node.npos)
				_FontData.Count = std::atoi(_Node.erase(0, 6).c_str()) + 1; // 1 is space

			if (_Node.find("file") != _Node.npos)
			{
				size_t first = _Node.find_first_of("\"") + 1;
				size_t last = _Node.find_last_of("\"");
				_FontData.AtlasPath = _Node.substr(first, last - first);
			}

			if (_Node.find("scaleW") != _Node.npos)
				_FontData.TileWidth = std::atoi(_Node.erase(0, 7).c_str());

			if (_Node.find("scaleH") != _Node.npos)
				_FontData.TileHeight = std::atoi(_Node.erase(0, 7).c_str());


			if (_Node == "char")
			{
				CharData _CharData;
				_File >> _Node;
				_CharData.AsciiCode = std::atoi(_Node.erase(0, 3).c_str()); // id= 
				_File >> _Node;
				_CharData.Xpos = std::atof(_Node.erase(0, 2).c_str()); // x=
				_File >> _Node;
				_CharData.Ypos = std::atof(_Node.erase(0, 2).c_str()); // y=
				_File >> _Node;
				_CharData.Width = std::atof(_Node.erase(0, 6).c_str()); // width=
				_File >> _Node;
				_CharData.Height = std::atof(_Node.erase(0, 7).c_str()); // height=
				_File >> _Node;
				_CharData.Xoffset = std::atof(_Node.erase(0, 8).c_str()); // xoffset=
				_File >> _Node;
				_CharData.Yoffset = std::atof(_Node.erase(0, 8).c_str()); // yoffset=
				_File >> _Node;
				_CharData.Xadvance = std::atof(_Node.erase(0, 9).c_str()); // xadvance=
				_FontData.CharsData[char(_CharData.AsciiCode)] = _CharData;
			}
		}

		_File.close();

		if (_FontData.AtlasPath.size())
		{
			int _Width, _Height, _Channels;
			std::string _AtlasPath = GetPath(filePath) + "/" + _FontData.AtlasPath;
			unsigned char* _Data = stbi_load(_AtlasPath.c_str(), &_Width, &_Height, &_Channels, STBI_rgb_alpha);
			if (_Data)
			{
				std::ofstream _File;
				_File.open(assetData->_Path, std::ios::binary);
				if (_File.is_open())
				{
					se::Binarizer::WriteNext<std::string>(_File, "#ShadeFont");
					se::Binarizer::WriteNext<int>(_File, _FontData.TileWidth);
					se::Binarizer::WriteNext<int>(_File, _FontData.TileHeight);
					se::Binarizer::WriteNext<int>(_File, _FontData.Count);
					// Font Data
					for (auto& _Char : _FontData.CharsData)
					{
						se::Binarizer::WriteNext<int>(_File, _Char.second.AsciiCode);
						se::Binarizer::WriteNext<float>(_File, _Char.second.Xpos);
						se::Binarizer::WriteNext<float>(_File, _Char.second.Ypos);
						se::Binarizer::WriteNext<float>(_File, _Char.second.Width);
						se::Binarizer::WriteNext<float>(_File, _Char.second.Height);
						se::Binarizer::WriteNext<float>(_File, _Char.second.Xoffset);
						se::Binarizer::WriteNext<float>(_File, _Char.second.Yoffset);
						se::Binarizer::WriteNext<float>(_File, _Char.second.Xadvance);
					}
					// Atlas Data
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
					throw se::ShadeException(std::string("Failed to save font atlas '" + filePath + "' !").c_str(), se::SECode::Warning);
				}

				stbi_image_free(_Data);
			}
			else
			{
				throw se::ShadeException(std::string("Cannot open source font altas file '" + _AtlasPath + "' !").c_str(), se::SECode::Warning);
			}

		}
		else
		{
			throw se::ShadeException(std::string("Cannot open source font altas file '" + GetPath(filePath) +"/"+ _FontData.AtlasPath + "' !").c_str(), se::SECode::Warning);
			
		}
	}
	else
	{
		throw se::ShadeException(std::string("Cannot open source font '" + filePath + "' !").c_str(), se::SECode::Warning);
	}

}

std::vector<AssimpMesh>  Serrializer::ProcessModel3DNode(const std::string& filePath, const aiNode* node, const aiScene* scene, se::AssetData& data)
{
	std::vector<AssimpMesh> _Meshes;

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		se::AssetData _Mesh;
		_Mesh._Name = mesh->mName.C_Str();
		_Mesh._Path = data._Path;
		_Mesh._Type = se::AssetDataType::Mesh;

		_Meshes.push_back(ProcessModel3DMesh(filePath, mesh, scene, i, _Mesh));
		data._Dependency.push_back(_Mesh);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		_Meshes = ProcessModel3DNode(filePath, node->mChildren[i], scene, data); // TODO THERE ! how to return if static 
	}

	return _Meshes;
}

AssimpMesh Serrializer::ProcessModel3DMesh(const std::string& filePath, aiMesh* mesh, const aiScene* scene, unsigned int id, se::AssetData& assetData)
{
	AssimpMesh _Mesh;
	_Mesh._Name = mesh->mName.C_Str();
	//Vertices
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
		}
		
		if (mesh->HasTextureCoords(0))
		{
			_Vertex.m_TextureCoords.x = mesh->mTextureCoords[0][i].x;
			_Vertex.m_TextureCoords.y = mesh->mTextureCoords[0][i].y;
		}

		_Mesh._Vertices.push_back(_Vertex);
	}
	//Indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace& face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			_Mesh._Indices.push_back(face.mIndices[j]);
		}
	}
	if (mesh->mMaterialIndex >= 0 && !filePath.empty())
	{
		se::AssetData _Image;
		se::AssetData _Material;
		aiColor3D     _AssimpColor;
		aiMaterial*   _Assimpmaterial = scene->mMaterials[mesh->mMaterialIndex];
		for (unsigned int i = 0; i < _Assimpmaterial->GetTextureCount(aiTextureType_DIFFUSE); i++)
		{
			aiString path;
			_Assimpmaterial->GetTexture(aiTextureType_DIFFUSE, i, &path);
			_Image._Name    = GetNameFromPath(path.C_Str());
			_Image._Type    = se::AssetDataType::Texture;
			_Image._SubType = se::AssetDataSubType::Diffuse;
			_Image._Path    = assetData._Path + _Image._Name + ".bin";
			SerrializeTexture(filePath + "/" + path.C_Str(), &_Image);
			assetData._Dependency.push_back(_Image);
		}
		for (unsigned int i = 0; i < _Assimpmaterial->GetTextureCount(aiTextureType_SPECULAR); i++)
		{
			aiString path;
			_Assimpmaterial->GetTexture(aiTextureType_SPECULAR, i, &path);
			_Image._Name    = GetNameFromPath(path.C_Str());
			_Image._Type    = se::AssetDataType::Texture;
			_Image._SubType = se::AssetDataSubType::Specular;
			_Image._Path = assetData._Path + _Image._Name + ".bin";
			SerrializeTexture(filePath + "/" + path.C_Str(), &_Image);
			assetData._Dependency.push_back(_Image);
		}
		for (unsigned int i = 0; i < _Assimpmaterial->GetTextureCount(aiTextureType_HEIGHT); i++)
		{
			aiString path;
			_Assimpmaterial->GetTexture(aiTextureType_HEIGHT, i, &path);
			_Image._Name    = GetNameFromPath(path.C_Str());
			_Image._Type    = se::AssetDataType::Texture;
			_Image._SubType = se::AssetDataSubType::NormalMap;
			_Image._Path = assetData._Path + _Image._Name + ".bin";
			SerrializeTexture(filePath + "/" + path.C_Str(), &_Image);
			assetData._Dependency.push_back(_Image);
		}

		_Mesh._Material.SetName(assetData._Name);
		_Assimpmaterial->Get(AI_MATKEY_COLOR_AMBIENT,      _AssimpColor); // Ka
		_Mesh._Material.SetAmbientColor(_AssimpColor.r,    _AssimpColor.g, _AssimpColor.b);
		_Assimpmaterial->Get(AI_MATKEY_COLOR_DIFFUSE,      _AssimpColor); // Kd
		_Mesh._Material.SetDiffuseColor(_AssimpColor.r,    _AssimpColor.g, _AssimpColor.b);
		_Assimpmaterial->Get(AI_MATKEY_COLOR_SPECULAR,     _AssimpColor);// Ks
		_Mesh._Material.SetSpecularColor(_AssimpColor.r,   _AssimpColor.g, _AssimpColor.b);
		_Assimpmaterial->Get(AI_MATKEY_COLOR_TRANSPARENT,  _AssimpColor); // Tf
		_Mesh._Material.SetTransparentMask(_AssimpColor.r, _AssimpColor.g, _AssimpColor.b);
		float value;
		_Assimpmaterial->Get(AI_MATKEY_SHININESS, value); // Ns
		_Mesh._Material.SetShinines(value);

		_Mesh._HasMaterial = true;
		
	}

	return _Mesh;
}

std::string Serrializer::ProcessShaderInclude(const std::string& filePath, const std::regex& pattern)
{
	std::ifstream _File;
	std::regex  include(".*#include[ ]*[\"<](.*)[\">].*");
	std::smatch includeMatch;

	_File.open(filePath, std::ios::binary);
	if (!_File.is_open())
		throw se::ShadeException(std::string("Failed to open shader include file '" + filePath + "' !").c_str(), se::SECode::Warning);

	std::string _ShadersSource;
	std::string line;
	while (_File.good())
	{
		std::getline(_File, line);

		if (std::regex_search(line, includeMatch, include))
		{
			_ShadersSource += ProcessShaderInclude(includeMatch[1], include);
			continue; //Next line to skip #include
		}

		_ShadersSource += "\n" + line;
		
	}

	_File.close();
	return _ShadersSource;
}
