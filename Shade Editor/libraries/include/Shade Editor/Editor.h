#pragma once
#include <string>
#include "Shade/Core/Engine/Entity.h"

class Editor
{
public:
	enum class ImportType
	{
		Model3D
	};
	static se::Entity Import(const ImportType& type, const std::string& filePath);
private:
	static se::Entity ImportModel3D(const std::string& filePath);
};

