#include "AssetLoader.h"
#include <Shade/Core/Render/Shader.h>

se::AssetLoader::AssetLoader()
{
}

se::AssetLoader::~AssetLoader()
{
}

const se::Asset* se::AssetLoader::Load(const se::AssetData* data)
{
	switch (data->_Type)
	{
		case AssetDataType::Shader:
		{
			/*auto* _Asset = se::Shader::Load(data);
			return _Asset;*/
		}
		default:
		{
			std::string msg = "Exeption : Undefined AssetDataType inse::AssetLoader::Load()";
			throw std::runtime_error(msg);
			break;
		}	
	}
}

