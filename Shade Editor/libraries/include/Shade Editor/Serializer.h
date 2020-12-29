#pragma once

#include <Shade/Core/Engine/Vertex.h>
#include <Shade/Core/Util/Binarizer.h>
#include <Shade/Core/Engine/AssetData.h>
//#include <Shade/Core/Util/ShadeException.h>

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>
#include "Vendors/stbi/stb_image.h"

struct Shader
{
	std::string path;
	std::string type;

};
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
	bool SerializeShader(const std::vector<Shader>& shaders, se::AssetData* data);
	bool SerializeImage(const std::string& filePath);
private:
	void processNode(const aiNode* node, const aiScene* scene);
	Model processMesh(aiMesh* mesh, const aiScene* scene, unsigned int id);
	std::string GetNameFromPath(const std::string& filePath);
	std::vector<Model> m_Meshes;
	std::string m_FilePath;
};

