#include "stdafx.h"
#include "Asset.h"
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Engine/AssetManager.h"

se::Asset::Asset() :
	m_AssetId(""), m_AssetData(nullptr) , m_IsInitialized(false)
{
}
se::Asset::~Asset()
{
	se::AssetManager::ImLast(m_AssetId);
	SE_DEBUG_PRINT(std::string("Asset '" + m_AssetId + "' has beed deleted").c_str(), se::SLCode::InfoPrimary);
}

void se::Asset::SetAssetData(se::AssetData& data)
{
	m_AssetData = &data;
}

const se::AssetData& se::Asset::GetAssetData() const
{
	return *m_AssetData;
}

const std::string& se::Asset::GetAssetID() const
{
	return m_AssetId;
}