#include "stdafx.h"
#include "Asset.h"
#include "Shade/Core/Util/Log.h"

se::Asset::Asset(const se::AssetData* data)
	:m_AssetData(data)
{
}
se::Asset::~Asset()
{
	SE_DEBUG_PRINT(std::string("Asset '" + m_AssetData->_Name + "' has beed deleted").c_str(), se::SLCode::InfoSecondary);
}
