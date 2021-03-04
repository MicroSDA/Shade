#include "Editor.h"
#include "AssimpModel3D.h"

se::Entity Editor::Import(const ImportType& type, const std::string& filePath)
{
	switch (type)
	{
	case ImportType::Model3D: return ImportModel3D(filePath);
	default:
		return se::Entity();
	}
}

se::Entity Editor::ImportModel3D(const std::string& filePath)
{
	AssimpModel3D* model3D = new AssimpModel3D();
	model3D->LoadFromFile(filePath);
	model3D->Init();

	auto modelEntity = se::Application::GetApplication().CreateEntity(se::Util::GetNameFromPath(filePath));
	modelEntity.AddComponent<se::Model3DComponent>(se::AssetPointer<se::Model3D>(static_cast<se::Model3D*>(model3D)));
	modelEntity.AddComponent<se::Transform3DComponent>();
	
	return modelEntity;
}