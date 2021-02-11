#pragma once
#include <string>

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
};

