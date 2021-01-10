#include "stdafx.h"
#include "Asset.h"
#include "Shade/Core/Util/Log.h"

se::Asset::Asset(const std::string& parrentClassName, const se::AssetData* data) :
	m_ParrentClassName(parrentClassName), m_AssetData(data) , m_IsInitialized(false)
{
}
se::Asset::~Asset()
{
	SE_DEBUG_PRINT(std::string("Asset '" + m_AssetData->_Name + "' has beed deleted").c_str(), se::SLCode::InfoSecondary);
}
