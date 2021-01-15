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
			se::AssetPointer<se::Asset> m_Ref;
			bool isKeepAlive           = true;
		};

		using ClassName = std::string;
		using Assets    = std::unordered_map<ClassName, AssetReferences>;
		using RoadMap   = std::unordered_map<ClassName, const se::AssetData*>;
	public:
		friend class Application;

		template<typename T>
		static se::AssetPointer<T> Hold(const ClassName& className)
		{
			auto& _Instance = GetInstance();
			// Trying to find in Assets map
			auto _AElement = _Instance.m_Assets.find(className);
			if (_AElement != _Instance.m_Assets.end())
			{
				// If already loaded
				auto _Ptr = dynamic_cast<T*>(_AElement->second.m_Ref.get());
				if (_Ptr)
				{
					return se::AssetPointer<T>(std::static_pointer_cast<T>(_AElement->second.m_Ref));
				}
				else
				{
					std::string _Msg("Error: Wrong asset assignment :'" + className + "'");
					throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
				}
			
			}
			else
			{
				// Trying to find in road map
				auto _RElement = _Instance.m_RoadMap.find(className);
				if (_RElement != _Instance.m_RoadMap.end())
				{
					// Load asset
					auto _Asset = new T(_RElement->first, _RElement->second);
					if (_Asset)
					{
						_Asset->Load();
						_Asset->Init(); // Temporary here 
						// Create asset ref and incease asset count + one ref;
						_Instance.m_Assets.emplace(std::pair<ClassName, AssetReferences>(className, AssetReferences { se::AssetPointer<se::Asset>(_Asset) , true}));
						return se::AssetPointer<T>(std::static_pointer_cast<T>(_Instance.m_Assets[className].m_Ref));
					}
					else 
					{
						std::string _Msg("Error: Wrong asset assignment :'" + className + "'");
						throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
					}
					
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
		static void Inseart(const ClassName& className, const se::AssetPointer<se::Asset>& asset);
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
		void _WriteRoadMap(std::ofstream& file, const se::AssetData& asset);
		void _ReadRoadMap();

		void ReadAssetsData(std::ifstream& file, se::AssetData& asset);
		void SetRoadMap(const se::AssetData* asset, std::unordered_map<std::string, const se::AssetData*>& map);
		static void Clear();
		static void Update();
		Assets    m_Assets;
		AssetData m_AssetsData;
		RoadMap   m_RoadMap;
	};
}