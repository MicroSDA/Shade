#include "AssetManager.h"
#include "core/render/Shader.h"

const se::Asset* se::AssetManager::Hold(const ClassName& className)
{
	return GetInstance()._Hold(className);
}

void se::AssetManager::WriteRoadMap(const se::AssetData& asset)
{
	std::ofstream file;

	file.open(ROAD_MAP_PATH, std::ofstream::binary);
	if (!file.is_open())
	{
#ifdef SE_DEBUG
		DEBUG_PRINT("Error: Road map file cannot be open in se::AssetManager::WriteRoadMap()", LogLevel::ERROR);
#else
		DEBUG_SAVE("", LogLevel::ERROR);
#endif // SE_DEBUG
		
	}
	else 
	{
		GetInstance()._WriteRoadMap(file, asset);
	}

	file.close();
}

void se::AssetManager::ReadRoadMap()
{
	GetInstance()._ReadRoadMap();
}
void se::AssetManager::_ReadRoadMap()
{
	try
	{
		std::ifstream file;
		file.open(ROAD_MAP_PATH, std::ifstream::binary);

		if (!file.is_open())
		{
			std::string msg = "Exeption : Open RoadMap faild in AssetManager::AssetManager()", SDL_GetError();
			throw std::runtime_error(msg);
		}


		ReadAssetsData(file, m_AssetsData);
		file.close();

		SetRoadMap(&m_AssetsData, m_RoadMap);

	}
	catch (std::runtime_error& error)
	{
#ifdef SE_DEBUG
		DEBUG_PRINT(error.what(), LogLevel::ERROR);
#else
		DEBUG_SAVE(error.what(), LogLevel::ERROR);
#endif // SE_DEBUG
		exit(-1);
	}
}


se::AssetManager::AssetManager()
{
}

se::AssetManager::~AssetManager()
{
}

se::AssetManager& se::AssetManager::GetInstance()
{
	static AssetManager _Instatnce;
	return _Instatnce;
}

const se::Asset* se::AssetManager::_Hold(const ClassName& className)
{
	try
	{
		if (m_RoadMap.find(className) != m_RoadMap.end())
		{
			if (m_Assets.find(className) != m_Assets.end())
			{
				return m_Assets.find(className)->second.m_Ref;
			}
			else
			{
				switch (m_RoadMap.find(className)->second->_Type)
				{
				case AssetDataType::Shader:
					return se::Shader::Load(m_RoadMap.find(className)->second);
					break;
				default:
					break;
				}

			}

			std::string msg = "Exeption : Specifaed class name \'" + className + "\' hasn't been found in AssetManager::Hold()";
			throw std::runtime_error(msg);
		}

		std::string msg = "Exeption : Specifaed class name \'"+className+"\' hasn't been found in AssetManager::Hold()";
		throw std::runtime_error(msg);
	}
	catch (std::runtime_error& error)
	{
#ifdef SE_DEBUG
		DEBUG_PRINT(error.what(), LogLevel::ERROR);
#else
		DEBUG_SAVE(error.what(), LogLevel::ERROR);
#endif // SE_DEBUG
		exit(-1);
	}
}

void se::AssetManager::_WriteRoadMap(std::ofstream& file, const se::AssetData& asset)
{
	se::Binarizer::WriteNext<std::string>(file, asset._Name);
	se::Binarizer::WriteNext<se::AssetDataType>(file, asset._Type);
	se::Binarizer::WriteNext<se::AssetDataSubType>(file, asset._SubType);
	se::Binarizer::WriteNext<std::string>(file, asset._Path);
	se::Binarizer::WriteNext<long long>(file, asset._Offset);
	se::Binarizer::WriteNext<size_t>(file, asset._Dependency.size());

	if (asset._Dependency.size())
	{
		for (auto& dependency : asset._Dependency)
		{
			_WriteRoadMap(file, dependency);
		}
	}
}


void se::AssetManager::ReadAssetsData(std::ifstream& file, se::AssetData& asset)
{
	asset._Name = se::Binarizer::ReadNext<std::string>(file);
	asset._Name.pop_back();// Remove \0
	asset._Type = se::Binarizer::ReadNext<se::AssetDataType>(file);
	asset._SubType = se::Binarizer::ReadNext<se::AssetDataSubType>(file);
	asset._Path   = se::Binarizer::ReadNext<std::string>(file);
	asset._Offset = se::Binarizer::ReadNext<long long>(file);
	size_t _DependencyCount = se::Binarizer::ReadNext<size_t>(file);

	if (_DependencyCount)
	{
		asset._Dependency.reserve(_DependencyCount);

		for (auto i = 0; i < _DependencyCount; i++)
		{
			asset._Dependency.emplace_back();
			asset._Dependency.back()._Parrent = &asset;
			ReadAssetsData(file, asset._Dependency[i]);
		}
	}
}

void se::AssetManager::SetRoadMap(const se::AssetData* asset, std::map<std::string, const se::AssetData*>& map)
{
	if (asset->_Parrent != nullptr)
		map[asset->_Parrent->_Name + "." + asset->_Name] = asset;
	else
		map[asset->_Name] = asset;
	
	for (auto i = 0; i < asset->_Dependency.size(); i++)
	{
		SetRoadMap(&asset->_Dependency[i], map);
	}
}
