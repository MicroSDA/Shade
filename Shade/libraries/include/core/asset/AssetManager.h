#pragma once
#include <utilities/Log.h>
#include <core/asset/Asset.h>
#include <utilities/Binarizer.h>
#include <map>
namespace se
{
	class SE_API AssetManager
	{
		struct AssetReferences
		{
			const Asset* m_Ref;
			unsigned int m_Count;
		};

		using ClassName = std::string;
		using Assets    = std::map<ClassName, AssetReferences>;
		using RoadMap   = std::map<ClassName, const se::AssetData*>;
	public:
		const static Asset* Hold(const ClassName& className);
		static void WriteRoadMap(const se::AssetData& asset);
		static void ReadRoadMap();
	private:
		//Singleton implementation
		AssetManager();
		~AssetManager();
		AssetManager(const AssetManager&) = delete;
		AssetManager& operator= (const AssetManager&) = delete;
		AssetManager(const AssetManager&&) = delete;
		AssetManager& operator= (const AssetManager&&) = delete;
		static AssetManager& GetInstance();
		/////////////////////////////////
		const Asset* _Hold(const ClassName& className);
		void _WriteRoadMap(std::ofstream& file, const se::AssetData& asset);
		void _ReadRoadMap();

		void ReadAssetsData(std::ifstream& file, se::AssetData& asset);
		void SetRoadMap(const se::AssetData* asset, std::map<std::string, const se::AssetData*>& map);

		Assets    m_Assets;
		AssetData m_AssetsData;
		RoadMap   m_RoadMap;
	};
}


