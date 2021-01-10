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
		using Assets = std::unordered_map<ClassName, AssetReferences>;
		using RoadMap = std::unordered_map<ClassName, const se::AssetData*>;
	public:
		template<typename T>
		static T* Hold(const ClassName& className)
		{
			auto& _Instance = GetInstance();
			// Trying to find in Assets map
			auto _AElement = _Instance.m_Assets.find(className);
			if (_AElement != _Instance.m_Assets.end())
			{
				// If already loaded
				
				if (dynamic_cast<T*>(_AElement->second.m_Ref))
				{
					_AElement->second.m_Count++;
					return static_cast<T*>(_AElement->second.m_Ref);
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
					auto* _Asset = dynamic_cast<T*>(new T(_RElement->first, _RElement->second));
					if (_Asset)
					{
						_Asset->Load();
						_Asset->Init(); // Temporary here 
						// Create asset ref and incease asset count + one ref;
						_Instance.m_Assets[className] = AssetReferences{ _Asset, 1 };
						return static_cast<T*>(_Asset);
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
		template<typename T>
		static T* Get(const ClassName& className)
		{
			auto& _Instance = GetInstance();

			auto _AElement = _Instance.m_Assets.find(className);
			if (_AElement != _Instance.m_Assets.end())
			{
				// If already loaded
				if (dynamic_cast<T*>(_AElement->second.m_Ref))
				{
					// _AElement->second.m_Count++; // Dont need there, potential issue ¯\_(ツ)_/¯
					return static_cast<T*>(_AElement->second.m_Ref);
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
					auto* _Asset = dynamic_cast<T*>(new T(_RElement->first, _RElement->second));

					if (_Asset)
					{
						_Asset->Load();
						_Asset->Init(); // Temporary here 
						// Create asset ref and incease asset count + one ref;
						_Instance.m_Assets[className] = AssetReferences{ _Asset, 1 };
						return static_cast<T*>(_Asset);
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
		void _Free(const ClassName& className);
		void _WriteRoadMap(std::ofstream& file, const se::AssetData& asset);
		void _ReadRoadMap();

		void ReadAssetsData(std::ifstream& file, se::AssetData& asset);
		void SetRoadMap(const se::AssetData* asset, std::unordered_map<std::string, const se::AssetData*>& map);

		Assets    m_Assets;
		AssetData m_AssetsData;
		RoadMap   m_RoadMap;
	};
}