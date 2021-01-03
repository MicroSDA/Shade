#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/AssetData.h"
#include "Shade/Core/Util/ShadeException.h"

namespace se
{
	class SE_API Asset
	{
	public:
		Asset(const std::string& parrentClassName, const se::AssetData* data); // ??
		virtual ~Asset();
		virtual void Load() = 0;
		virtual void Init() = 0;
	protected:
		const se::AssetData* m_AssetData;
		const std::string    m_ParrentClassName;
	private:
	};
}


