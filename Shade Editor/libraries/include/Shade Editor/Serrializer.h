#pragma once
#include <Shade/Core/Engine/Vertex.h>
#include <Shade/Core/Util/Binarizer.h>
#include <Shade/Core/Engine/AssetData.h>
#include <Shade/Core/Engine/Material.h>

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>
#include "Vendors/stbi/stb_image.h"

struct ShaderMeta
{
	std::string _Path;
	std::string _Type;
};

struct AssimpMesh
{
	std::string               _Name; // TODO Implement in asset data and file
	se::Material              _Material;
	std::vector<se::Vertex>   _Vertices;
	std::vector<unsigned int> _Indices;
	bool                      _HasMaterial = false;
};

class Serrializer
{
public:
	//static void Sirrialize(se::AssetData& assetData);
	static void Serrialize3DModel(const std::string& filePath, se::AssetData* const& assetData = NULL, const bool& withDeps = false);
	static void SerrializeTexture(const std::string& filePath, se::AssetData* const& assetData = NULL, const bool& withDeps = false);
	static void SerrializeMaterial(const std::string& filePath, const std::vector<se::Material>& materials, se::AssetData* const& assetData = NULL);
	static void SerrializeShader(const std::vector<ShaderMeta>& shaders, se::AssetData* const& assetData = NULL);
	static void SerrializeFont(const std::string& filePath, se::AssetData* const& assetData = NULL, const bool& withDeps = false);
private:
	//static       std::string m_PacketPath;
	//static void  SirrializeRecursively(se::AssetData& assetData);
	static std::string GetNameFromPath(const std::string& filePath);
	static std::string GetPath(const std::string& filePath);

	static std::vector<AssimpMesh> ProcessModel3DNode(const std::string& filePath, const aiNode* node, const aiScene* scene, se::AssetData& data);
	static AssimpMesh  ProcessModel3DMesh(const std::string& filePath, aiMesh* mesh, const aiScene* scene, unsigned int id, se::AssetData& data);
	static std::string ProcessShaderInclude(const std::string& filePath, const std::regex& pattern);
};

