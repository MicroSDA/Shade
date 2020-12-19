#include "AssetManager.h"
#include <Shade/Core/Asset/AssetLoader.h>

se::AssetManager::AssetManager()
{
}

se::AssetManager::~AssetManager()
{
}

void se::AssetManager::Free(const ClassName& className)
{
	GetInstance()._Free(className);
}

void se::AssetManager::_Free(const ClassName& className)
{
	auto _AElement = m_Assets.find(className);

	if (_AElement != m_Assets.end())
	{
		// Discrase count of refs
		if (_AElement->second.m_Count > 1)
		{
			_AElement->second.m_Count--;
		}
		else 
		{
			delete _AElement->second.m_Ref;
			m_Assets.erase(_AElement);
		}
	}
	else
	{
#ifdef SE_DEBUG
		DEBUG_PRINT("Error: Trying to free unloaded asset '"+ className +"'", LogLevel::ERROR);
#else
		DEBUG_SAVE("Error: Trying to free unloaded asset '" + className + "'", LogLevel::ERROR);
#endif // SE_DEBUG
		exit(-1);
	}
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
		DEBUG_SAVE("Error: Road map file cannot be open in se::AssetManager::WriteRoadMap()", LogLevel::ERROR);
#endif // SE_DEBUG
		exit(-1);
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

se::AssetManager& se::AssetManager::GetInstance()
{
	static AssetManager _Instatnce;
	return _Instatnce;
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
	{
		auto* _Parrent = asset->_Parrent;
		std::string name;
		while (_Parrent != nullptr)
		{
			name = _Parrent->_Name + "." + name;
			_Parrent = _Parrent->_Parrent;
		}

		map[name + asset->_Name] = asset;
	}
	else
	{
		map[asset->_Name] = asset;
	}
		
	
	for (auto i = 0; i < asset->_Dependency.size(); i++)
	{
		SetRoadMap(&asset->_Dependency[i], map);
	}
}
