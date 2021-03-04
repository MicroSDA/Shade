#include "AssimpModel3D.h"

bool AssimpModel3D::LoadFromFile(const std::string& filePath)
{
	Assimp::Importer importer;
	const aiScene* m_pScene = importer.ReadFile(filePath,
		aiProcess_FlipUVs |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_CalcTangentSpace |
		aiProcess_FixInfacingNormals |
		aiProcess_GenSmoothNormals);

	if (!m_pScene)
	{
		return false;
	}
	else
	{
		m_ImportedAssetData.ID   = se::Util::GetNameFromPath(filePath);
		m_ImportedAssetData.Path = filePath;
		m_ImportedAssetData.Type = se::AssetData::AType::Model3D;

		ProcessModel3DNode(filePath.c_str(), m_pScene->mRootNode, m_pScene);
		return true;
	}
}

const se::AssetData* AssimpModel3D::GetImportedAssetData() const
{
	return m_AssetData;
}

void AssimpModel3D::ProcessModel3DNode(const char* filePath ,const aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		ProcessModel3DMesh(filePath, mesh, scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessModel3DNode(filePath, node->mChildren[i], scene); // TODO THERE ! how to return if static 
	}
}

void AssimpModel3D::ProcessModel3DMesh(const char* filePath, aiMesh* mesh, const aiScene* scene)
{
	std::vector<se::Vertex>   vertices;
	std::vector<unsigned int> indices;
	vertices.reserve(mesh->mNumVertices);
	indices.reserve(mesh->mNumFaces);

	se::AssetPointer<se::Mesh> pMesh(new se::Mesh());
	se::AssetData assetDataMesh;

	pMesh->SetAssetData(assetDataMesh);
	auto meshEntity = this->CreateEntity(mesh->mName.C_Str());
	meshEntity.AddComponent<se::MeshComponent>(pMesh);

	//Vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		se::Vertex vertex;
		vertex.m_Position.x = mesh->mVertices[i].x;
		vertex.m_Position.y = mesh->mVertices[i].y;
		vertex.m_Position.z = mesh->mVertices[i].z;
		if (mesh->HasNormals())
		{
			vertex.m_Normals.x = mesh->mNormals[i].x;
			vertex.m_Normals.y = mesh->mNormals[i].y;
			vertex.m_Normals.z = mesh->mNormals[i].z;
			if (mesh->HasTangentsAndBitangents())
			{
				vertex.m_Tangents.x = mesh->mTangents[i].x;
				vertex.m_Tangents.y = mesh->mTangents[i].y;
				vertex.m_Tangents.z = mesh->mTangents[i].z;
			}
		}

		if (mesh->HasTextureCoords(0))
		{
			vertex.m_TextureCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.m_TextureCoords.y = mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}
	//Indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace& face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	if (mesh->mMaterialIndex >= 0 )
	{
		se::AssetData _Image;
		se::AssetData _Material;
		aiColor3D     _AssimpColor;
		aiMaterial*   _Assimpmaterial = scene->mMaterials[mesh->mMaterialIndex];
		for (unsigned int i = 0; i < _Assimpmaterial->GetTextureCount(aiTextureType_DIFFUSE); i++)
		{
			aiString path;
			_Assimpmaterial->GetTexture(aiTextureType_DIFFUSE, i, &path);
			_Image.ID      = se::Util::GetNameFromPath(path.C_Str());
			_Image.Type    = se::AssetData::AType::Texture;
			_Image.SubType = se::AssetData::ASubType::Diffuse;
			_Image.Path = path.C_Str();

			auto _TextureEntity = pMesh->CreateEntity(_Assimpmaterial->GetName().C_Str());
			AssimpTexture* pTexture = new AssimpTexture();
			std::string _path = se::Util::GetPath(filePath) + "/" + path.C_Str();

			pTexture->SetImportedAssetData(&_Image);
			pTexture->LoadFromFile(_path.c_str());
			pTexture->Init();
			_TextureEntity.AddComponent<se::TextureComponent>(se::AssetPointer<se::Texture>(static_cast<se::Texture*>(pTexture)));
		}
		for (unsigned int i = 0; i < _Assimpmaterial->GetTextureCount(aiTextureType_SPECULAR); i++)
		{
			aiString path;
			_Assimpmaterial->GetTexture(aiTextureType_SPECULAR, i, &path);
			_Image.ID      = se::Util::GetNameFromPath(path.C_Str());
			_Image.Type    = se::AssetData::AType::Texture;
			_Image.SubType = se::AssetData::ASubType::Specular;
			_Image.Path    = path.C_Str();

			auto _TextureEntity = pMesh->CreateEntity(_Image.ID);
			AssimpTexture* pTexture = new AssimpTexture();
			std::string _path = se::Util::GetPath(filePath) + "/" + path.C_Str();
		
			pTexture->SetImportedAssetData(&_Image);
			pTexture->LoadFromFile(_path.c_str());
			pTexture->Init();
			_TextureEntity.AddComponent<se::TextureComponent>(se::AssetPointer<se::Texture>(static_cast<se::Texture*>(pTexture)));
		}
		for (unsigned int i = 0; i < _Assimpmaterial->GetTextureCount(aiTextureType_HEIGHT); i++)
		{
			aiString path;
			_Assimpmaterial->GetTexture(aiTextureType_HEIGHT, i, &path);
			_Image.ID      = se::Util::GetNameFromPath(path.C_Str());
			_Image.Type    = se::AssetData::AType::Texture;
			_Image.SubType = se::AssetData::ASubType::NormalMap;
			_Image.Path    = path.C_Str();

			auto _TextureEntity = pMesh->CreateEntity(_Image.ID);
			AssimpTexture* pTexture = new AssimpTexture();
			std::string _path = se::Util::GetPath(filePath) + "/" + path.C_Str();

			pTexture->SetImportedAssetData(&_Image);
			pTexture->LoadFromFile(_path.c_str());
			pTexture->Init();
			_TextureEntity.AddComponent<se::TextureComponent>(se::AssetPointer<se::Texture>(static_cast<se::Texture*>(pTexture)));
		}

		se::Material material;

		material.SetName("Material");
		_Assimpmaterial->Get(AI_MATKEY_COLOR_AMBIENT, _AssimpColor); // Ka
		material.SetAmbientColor(_AssimpColor.r, _AssimpColor.g, _AssimpColor.b);
		_Assimpmaterial->Get(AI_MATKEY_COLOR_DIFFUSE, _AssimpColor); // Kd
		material.SetDiffuseColor(_AssimpColor.r, _AssimpColor.g, _AssimpColor.b);
		_Assimpmaterial->Get(AI_MATKEY_COLOR_SPECULAR, _AssimpColor);// Ks
		material.SetSpecularColor(_AssimpColor.r, _AssimpColor.g, _AssimpColor.b);
		_Assimpmaterial->Get(AI_MATKEY_COLOR_TRANSPARENT, _AssimpColor); // Tf
		material.SetTransparentMask(_AssimpColor.r, _AssimpColor.g, _AssimpColor.b);
		float value;
		_Assimpmaterial->Get(AI_MATKEY_SHININESS, value); // Ns
		material.SetShininess(value);

		
		pMesh->SetIndices(indices);
		pMesh->SetVertices(vertices);

		
		meshEntity.AddComponent<se::MaterialComponent>(material);
		//entity.AddComponent<se::MeshComponent>(pMesh);
	}

}
