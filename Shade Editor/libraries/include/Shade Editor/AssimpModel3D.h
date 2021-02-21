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
#include <Shade/Core/Util/Util.h>
#include "AssimpTexture.h"

class AssimpModel3D : public se::Model3D
{
public:
	AssimpModel3D() {};
	virtual ~AssimpModel3D() {};
	bool LoadFromFile(const std::string& filePath);
private:
	void ProcessModel3DNode(const char* filename, const aiNode* node, const aiScene* scene);
	void ProcessModel3DMesh(const char* filename, aiMesh* mesh, const aiScene* scene);
};
