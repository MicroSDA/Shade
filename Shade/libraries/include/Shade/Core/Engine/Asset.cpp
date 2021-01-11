#include "stdafx.h"
#include "Asset.h"
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Engine/AssetManager.h"

se::Asset::Asset(const std::string& fullClassName, const se::AssetData* data) :
	m_FullClassName(fullClassName), m_AssetData(data) , m_IsInitialized(false)
{
}
se::Asset::~Asset()
{
	SE_DEBUG_PRINT(std::string("Asset '" + m_FullClassName + "' has beed deleted").c_str(), se::SLCode::InfoSecondary);
}

const se::AssetData* se::Asset::GetAssetData() const
{
	return m_AssetData;
}

std::string se::Asset::GetAssetClassName() const
{
	return m_FullClassName;
}
