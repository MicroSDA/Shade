#include "Editor.h"

bool Editor::Import(const ImportType& type, const std::string& filePath)
{
	switch (type)
	{
	case ImportType::Model3D: return ImportModel3D(filePath);
	default:
		return false;
	}
}

bool Editor::ImportModel3D(const std::string& filePath)
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
		se::AssetData assetData;
		se::AssetPointer<se::Model3D> model3D(new se::Model3D("", &assetData));

		se::Entity model3DEntity = se::Application::GetApplication().GetCurrentScene()->CreateEntity();
		
		model3DEntity.AddComponent<se::Model3DComponent>(model3D);

		ProcessModel3DNode(model3DEntity, m_pScene->mRootNode, m_pScene);
		return true;
	}
}

void Editor::ProcessModel3DNode(se::Entity& entity, const aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		se::Entity meshEntity = entity.GetComponent<se::Model3DComponent>().Model3D->CreateEntity();
		ProcessModel3DMesh(meshEntity, mesh, scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessModel3DNode(entity, node->mChildren[i], scene); // TODO THERE ! how to return if static 
	}
}

void Editor::ProcessModel3DMesh(se::Entity& entity, aiMesh* mesh, const aiScene* scene)
{
	se::AssetPointer<se::Mesh> pMesh;
	entity.AddComponent<se::MeshComponent>(pMesh);
}
