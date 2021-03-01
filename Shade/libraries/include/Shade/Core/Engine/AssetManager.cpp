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

void se::AssetManager::Free(const std::string& assetId)
{
	auto& _Instance = GetInstance();
	auto _AElement = _Instance.m_Assets.find(assetId);

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
				SE_DEBUG_PRINT(std::string("Warning: Trying to free asset '" + assetId + "' which has more then one uses count.").c_str(), se::SLCode::Warning);
			}

		}
		else
		{
			SE_DEBUG_PRINT(std::string("Warning: Trying to free weak asset '" + assetId + "'.").c_str(), se::SLCode::Warning);
		}
	}
	else
	{
		SE_DEBUG_PRINT(std::string("Warning: Trying to free unloaded asset '" + assetId + "'.").c_str(), se::SLCode::Warning);
	}

}

void se::AssetManager::WriteAssetDataList(const std::string& filePath, const se::AssetData& asset)
{
	std::ofstream _File;
	_File.open(filePath, std::ofstream::binary);
	if (!_File.is_open())
	{
		throw se::ShadeException("Error: Road map file cannot be open!", se::SECode::Error);
	}
	else
	{
		GetInstance().WriteAssetDataListRecursively(_File, asset);
	}

	_File.close();
}

void se::AssetManager::ReadAssetDataList(const std::string& filePath)
{
	auto& instance = GetInstance();

	std::ifstream _File;
	_File.open(filePath, std::ifstream::binary); //TODO resolve issue with path 

	if (!_File.is_open())
	{
		throw se::ShadeException("Error: Road map file cannot be open!", se::SECode::Error);
	}

	// Clear if it was loaded before
	instance.m_AssetsData = se::AssetData();
	instance.m_AssetDataList.clear();

	instance.ReadAssetsData(_File, instance.m_AssetsData);
	_File.close();
	instance.SetRoadMap(&instance.m_AssetsData, instance.m_AssetDataList);
}
const se::AssetData& se::AssetManager::GetAssetDataList()
{
	return GetInstance().m_AssetsData;
}

void se::AssetManager::ImLast(const std::string& assetId) 
{
	
	auto& _Instance = GetInstance();
	if (!_Instance.m_ImDestructing)
	{
		auto _AElement = _Instance.m_Assets.find(assetId);
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

void se::AssetManager::WriteAssetDataListRecursively(std::ofstream& file, const se::AssetData& asset)
{
	se::Binarizer::WriteNext<std::string>(file, asset.ID);
	se::Binarizer::WriteNext<se::AssetData::AType>(file, asset.Type);
	se::Binarizer::WriteNext<se::AssetData::ASubType>(file, asset.SubType);
	se::Binarizer::WriteNext<std::string>(file, asset.Path);
	se::Binarizer::WriteNext<uint32_t>(file, asset.Offset);
	se::Binarizer::WriteNext<uint32_t>(file, static_cast<uint32_t>(asset.Childs.size()));

	if (asset.Childs.size())
	{
		for (auto& dependency : asset.Childs)
		{
			WriteAssetDataListRecursively(file, dependency);
		}
	}
}


void se::AssetManager::ReadAssetsData(std::ifstream& file, se::AssetData& asset)
{

	asset.ID = se::Binarizer::ReadNext<std::string>(file);
	asset.ID.pop_back();// Remove \0
	asset.Type = se::Binarizer::ReadNext<se::AssetData::AType>(file);
	asset.SubType = se::Binarizer::ReadNext<se::AssetData::ASubType>(file);
	asset.Path = se::Binarizer::ReadNext<std::string>(file);
	asset.Path.pop_back();// Remove \0
	asset.Offset = se::Binarizer::ReadNext<uint32_t>(file);

	uint32_t childsCount = se::Binarizer::ReadNext<uint32_t>(file);

	if (childsCount)
	{
		asset.Childs.reserve(childsCount);

		for (uint32_t i = 0; i < childsCount; i++)
		{
			asset.Childs.emplace_back();
			asset.Childs.back().Parrent = &asset;
			ReadAssetsData(file, asset.Childs[i]);
		}
	}
}

void se::AssetManager::SetRoadMap(const se::AssetData* asset, std::unordered_map<std::string, const se::AssetData*>& map)
{
	if (asset->Parrent != nullptr)
	{
		auto* _Parrent = asset->Parrent;
		std::string name;
		while (_Parrent != nullptr && !_Parrent->ID.empty())
		{
			name = _Parrent->ID + "." + name;
			_Parrent = _Parrent->Parrent;
		}

		map[name + asset->ID] = asset;
	}
	else
	{
		map[asset->ID] = asset;
	}


	for (auto i = 0; i < asset->Childs.size(); i++)
	{
		SetRoadMap(&asset->Childs[i], map);
	}
}
