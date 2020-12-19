#pragma once
#include <Shade/Core/Asset/Asset.h>

namespace se
{
	class AssetLoader
	{
	public:
		static const se::Asset* Load(const se::AssetData* data);
	private:
		//Singleton implementation
		AssetLoader();
		~AssetLoader();
		AssetLoader(const AssetLoader&) = delete;
		AssetLoader& operator= (const AssetLoader&) = delete;
		AssetLoader(const AssetLoader&&) = delete;
		AssetLoader& operator= (const AssetLoader&&) = delete;
	};
}


