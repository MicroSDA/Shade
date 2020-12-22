#pragma once
#include "Shade/Core/Engine/Asset.h"
#include "Shade/Core/Util/Binarizer.h"
#include "Shade/Core/Util/ShadeException.h"

namespace se
{
	class SE_API AssetManager
	{
		struct AssetReferences
		{
			se::Asset* m_Ref;
			unsigned int m_Count = 0;
		};

		using ClassName = std::string;
		using Assets = std::map<ClassName, AssetReferences>;
		using RoadMap = std::map<ClassName, const se::AssetData*>;
	public:

		template<typename T>
		static T* Hold(const ClassName& className)
		{
			auto* _Asset = dynamic_cast<T*>(GetInstance()._Hold<T>(className));

			if (_Asset)
			{
				return _Asset;
			}
			else
			{
				std::string _Msg("Error: Wrong asset assignment :'" + className + "'");
				throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
			}
		}
		static void Free(const ClassName& className);

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
		template<typename T>
		se::Asset* _Hold(const ClassName& className);
		void _Free(const ClassName& className);
		void _WriteRoadMap(std::ofstream& file, const se::AssetData& asset);
		void _ReadRoadMap();

		void ReadAssetsData(std::ifstream& file, se::AssetData& asset);
		void SetRoadMap(const se::AssetData* asset, std::map<std::string, const se::AssetData*>& map);

		Assets    m_Assets;
		AssetData m_AssetsData;
		RoadMap   m_RoadMap;
	};
}

template<typename T>
se::Asset* se::AssetManager::_Hold(const ClassName& className)
{
	// Trying to find in Assets map
	auto _AElement = m_Assets.find(className);
	if (_AElement != m_Assets.end())
	{
		// If already loaded
		_AElement->second.m_Count++;
		return _AElement->second.m_Ref;
	}
	else
	{
		// Trying to find in road map
		auto _RElement = m_RoadMap.find(className);
		if (_RElement != m_RoadMap.end())
		{
			// Load asset
			auto* _Asset = new T(_RElement->second);
			_Asset->Load();
			// Create asset ref and incease asset count + one ref;
			m_Assets.insert(std::pair<ClassName, AssetReferences>(className, AssetReferences{ _Asset, 1 }));
			return _Asset;
		}
		else
		{
			std::string _Msg("Exeption : Specifaed class name '" + className + "' hasn't been found");
			throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
		}

		std::string _Msg("Exeption : Specifaed class name '" + className + "' hasn't been found");
		throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
	}

}

