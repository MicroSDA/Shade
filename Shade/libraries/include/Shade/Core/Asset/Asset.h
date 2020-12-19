#pragma once
#include <Shade/Core/Asset/AssetData.h>

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


