#pragma once

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>
#include "Vendors/stbi/stb_image.h"
#include <Shade/Core/Engine/Entity.h>
#include <Shade/Core/Engine/Application.h>
#include <Shade/Core/Engine/Components.h>
#include <Shade/Core/Engine/DrawableComponents.h>
#include <Shade/Core/Engine/TransformComponents.h>

class Editor
{
public:
	enum class ImportType
	{
		Model3D
	};
	static bool Import(const ImportType& type, const std::string& filePath);
private:
	static bool ImportModel3D(const std::string& filePath);
	static void ProcessModel3DNode(se::Entity& entity, const aiNode* node, const aiScene* scene);
	static void ProcessModel3DMesh(se::Entity& entity, aiMesh* mesh, const aiScene* scene);
};

