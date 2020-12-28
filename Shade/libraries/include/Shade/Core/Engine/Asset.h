#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/AssetData.h"
#include "Shade/Core/Util/ShadeException.h"

namespace se
{
	class SE_API Asset
	{
	public:
		Asset(const se::AssetData* data); // ??
		virtual ~Asset();
		virtual void Load() = 0;
	protected:
		const se::AssetData* m_AssetData;
	private:
	};
}


