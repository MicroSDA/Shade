#include "stdafx.h"
#include "AssetManager.h"
#include "Shade/Core/Util/Log.h"


se::AssetManager::AssetManager()
{
}

se::AssetManager::~AssetManager()
{
	// Trying to evade recursive deleting
	GetInstance().m_ImDestructing = true;
}

void se::AssetManager::Clear()
{
	// Trying to evade recursive deleting
	GetInstance().m_ImDestructing = true;
	GetInstance().m_Assets.clear();
}

void se::AssetManager::Free(const std::string& className)
{
	auto& _Instance = GetInstance();
	auto _AElement = _Instance.m_Assets.find(className);

	if (_AElement != _Instance.m_Assets.end())
	{

		if (std::get_if<se::AssetPointer<se::Asset>>(&_AElement->second.m_Ref))
		{
			if (std::get<se::AssetPointer<se::Asset>>(_AElement->second.m_Ref).use_count() == 1)
			{
				_Instance.m_Assets.erase(_AElement);
			}
			else
			{
				SE_DEBUG_PRINT(std::string("Warning: Trying to free asset '" + className + "' which has more then one uses count.").c_str(), se::SLCode::Warning);
			}

		}
		else
		{
			SE_DEBUG_PRINT(std::string("Warning: Trying to free weak asset '" + className + "'.").c_str(), se::SLCode::Warning);
		}
	}
	else
	{
		SE_DEBUG_PRINT(std::string("Warning: Trying to free unloaded asset '" + className + "'.").c_str(), se::SLCode::Warning);
	}

}

void se::AssetManager::WriteRoadMap(const se::AssetData& asset)
{
	std::ofstream _File;
	_File.open("./project/RoadMap.bin", std::ofstream::binary);
	if (!_File.is_open())
	{
		throw se::ShadeException("Error: Road map file cannot be open!", se::SECode::Error);
	}
	else
	{
		GetInstance()._WriteRoadMap(_File, asset);
	}

	_File.close();
}

void se::AssetManager::ReadRoadMap()
{
	GetInstance()._ReadRoadMap();
}
void se::AssetManager::_ReadRoadMap()
{

	std::ifstream _File;
	_File.open("././project/RoadMap.bin", std::ifstream::binary); //TODO resolve issue with path 

	if (!_File.is_open())
	{
		throw se::ShadeException("Error: Road map file cannot be open!", se::SECode::Error);
	}

	// Clear if it was loaded before
	m_AssetsData = se::AssetData();
	m_RoadMap.clear();

	ReadAssetsData(_File, m_AssetsData);
	_File.close();
	SetRoadMap(&m_AssetsData, m_RoadMap);

}

void se::AssetManager::ImLast(const std::string& className) 
{
	
	auto& _Instance = GetInstance();
	if (!_Instance.m_ImDestructing)
	{
		auto _AElement = _Instance.m_Assets.find(className);
		if (_AElement != _Instance.m_Assets.end())
		{
			_Instance.m_Assets.erase(_AElement);
		}
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
	se::Binarizer::WriteNext<uint32_t>(file, (uint32_t)asset._Dependency.size());

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
	asset._Path = se::Binarizer::ReadNext<std::string>(file);
	asset._Path.pop_back();// Remove \0
	asset._Offset = se::Binarizer::ReadNext<long long>(file);
	uint32_t _DependencyCount = se::Binarizer::ReadNext<uint32_t>(file);

	if (_DependencyCount)
	{
		asset._Dependency.reserve(_DependencyCount);

		for (uint32_t i = 0; i < _DependencyCount; i++)
		{
			asset._Dependency.emplace_back();
			asset._Dependency.back()._Parrent = &asset;
			ReadAssetsData(file, asset._Dependency[i]);
		}
	}
}

void se::AssetManager::SetRoadMap(const se::AssetData* asset, std::unordered_map<std::string, const se::AssetData*>& map)
{
	if (asset->_Parrent != nullptr)
	{
		auto* _Parrent = asset->_Parrent;
		std::string name;
		while (_Parrent != nullptr && !_Parrent->_Name.empty())
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
