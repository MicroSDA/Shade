#pragma once

#include <Shade/Core/Engine/Vertex.h>
#include <Shade/Core/Util/Binarizer.h>
#include <iostream>
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

struct Model
{
	std::string name;
	std::vector<se::Vertex> vertices;
	std::vector<unsigned int> indices;
};

class Serializer
{
public:
	Serializer();
	~Serializer();
	bool SerializeModel(const std::string& filePath);
private:
	void processNode(const aiNode* node, const aiScene* scene);
	Model processMesh(aiMesh* mesh, const aiScene* scene, unsigned int id);

	std::vector<Model> m_Meshes;
	std::string m_FilePath;
};

