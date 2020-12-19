#pragma once
#include <Shade/Core/Asset/Asset.h>
#include <Shade/Utilities/Log.h>
#include <Shade/Utilities/Binarizer.h>

#include <map>

namespace se
{
	class SE_API AssetManager
	{
		struct AssetReferences
		{
			const se::Asset* m_Ref;
			unsigned int m_Count = 0;
		};

		using ClassName = std::string;
		using Assets    = std::map<ClassName, AssetReferences>;
		using RoadMap   = std::map<ClassName, const se::AssetData*>;
	public:

		template<typename T>
		static const T* Hold(const ClassName& className)
		{
			auto* _Asset = dynamic_cast<const T*>(GetInstance()._Hold<T>(className));

			if (_Asset)
			{
				return _Asset;
			}
			else 
			{
#ifdef SE_DEBUG
				DEBUG_PRINT("Error: Wrong asset assignment :'" + className + "'", LogLevel::ERROR);
#else
				DEBUG_SAVE("Error: Wrong asset assignment :'" + className + "'", LogLevel::ERROR);
#endif // SE_DEBUG
				exit(-1);
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
		const se::Asset* _Hold(const ClassName& className);
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
const se::Asset* se::AssetManager::_Hold(const ClassName& className)
{
	try
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
				std::string msg = "Exeption : Specifaed class name '" + className + "' hasn't been found in AssetManager::Hold()";
				throw std::runtime_error(msg);
			}

			std::string msg = "Exeption : Specifaed class name '" + className + "' hasn't been found in AssetManager::Hold()";
			throw std::runtime_error(msg);
		}
	}
	catch (std::runtime_error& error)
	{
#ifdef SE_DEBUG
		DEBUG_PRINT(error.what(), LogLevel::ERROR);
#else
		DEBUG_SAVE(error.what(), LogLevel::ERROR);
#endif // SE_DEBUG
		exit(-1);
	}
}

