#include "stdafx.h"
#include "Serializer.h"

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
		//return true;
	}

	//////////////////////
	std::string new_name = m_FilePath;
	std::size_t extension = new_name.find_last_of(".");
	new_name.erase(extension);
	new_name += ".bin";

	std::ofstream _File;
	_File.open(new_name, std::ios::binary);

	se::Binarizer::WriteNext<std::string>(_File, "#ShadeModel3D");
	se::Binarizer::WriteNext<unsigned int>(_File, m_Meshes.size());

	for (auto& mesh : m_Meshes)
	{
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

	std::vector<se::Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		se::Vertex vertex;

		vertex.m_Position.x = mesh->mVertices[i].x;
		vertex.m_Position.y = mesh->mVertices[i].y;
		vertex.m_Position.z = mesh->mVertices[i].z;

		if (mesh->HasNormals()) {

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
		else {

			//TODO: if noramls doesnt exist
		}

		if (mesh->HasTextureCoords(0)) {


			vertex.m_TextureCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.m_TextureCoords.y = mesh->mTextureCoords[0][i].y;

		}
		else {
			//TODO: if textCoors doesnt exist
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace& face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Model model;

	model.name = mesh->mName.data;
	model.vertices = vertices;
	model.indices = indices;

	return model;
}
