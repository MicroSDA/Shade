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
			std::variant<se::AssetPointerWeak<se::Asset>, se::AssetPointer<se::Asset>> m_Ref;
		};

		using ClassName = std::string;
		using Assets    = std::unordered_map<ClassName, AssetReferences>;
		using RoadMap   = std::unordered_map<ClassName, const se::AssetData*>;
	public:
		friend class Application;
		friend class Asset;
		template<typename T>
		static se::AssetPointer<T> Hold(const ClassName& className, bool keepAlive = true)
		{
			auto& _Instance = GetInstance();
			// Trying to find in Assets map
			auto _AElement = _Instance.m_Assets.find(className);
			if (_AElement != _Instance.m_Assets.end())
			{
				// If already loaded
				se::AssetPointer<se::Asset> _Out;
				if (std::get_if<se::AssetPointerWeak<se::Asset>>(&_AElement->second.m_Ref))
				{
					
					auto& _Weak = std::get<se::AssetPointerWeak<se::Asset>>(_AElement->second.m_Ref);
					if (_Weak.expired())
					{
						goto load_new;
					}
					else
					{
						auto _pAsset = dynamic_cast<T*>(_Weak.lock().get());
						{
							if (_pAsset)
							{
								_Out = std::get<se::AssetPointerWeak<se::Asset>>(_AElement->second.m_Ref).lock();
								return se::AssetPointer<T>(std::static_pointer_cast<T>(_Out));
							}
							else
							{
								std::string _Msg("Error: Wrong asset assignment :'" + className + "'");
								throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
							}
						}
					}

				}
				else if (std::get_if<se::AssetPointer<se::Asset>>(&_AElement->second.m_Ref))
				{
					auto _Ptr = dynamic_cast<T*>(std::get<se::AssetPointer<se::Asset>>(_AElement->second.m_Ref).get());
					if (_Ptr)
					{
						//_Out = std::get<se::AssetPointerWeak<se::Asset>>(_AElement->second.m_Ref).lock();
						return se::AssetPointer<T>(std::static_pointer_cast<T>(std::get<se::AssetPointer<se::Asset>>(_AElement->second.m_Ref)));
					}
					else
					{
						std::string _Msg("Error: Wrong asset assignment :'" + className + "'");
						throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
					}
				}
					
			}
			else
			{
			load_new:
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
						se::AssetPointer<se::Asset> _Ptr(_Asset);
						if (keepAlive)
						{
							_Instance.m_Assets.emplace(std::pair<ClassName, AssetReferences>(className, AssetReferences{ _Ptr }));
						}
						else
						{
							_Instance.m_Assets.emplace(std::pair<ClassName, AssetReferences>(className, AssetReferences{ se::AssetPointerWeak<se::Asset>(_Ptr) }));
						}
					
						return se::AssetPointer<T>(std::static_pointer_cast<T>(_Ptr));
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
		static void Free(const std::string& className);
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
		static void ImLast(const std::string& className) ;
		void ReadAssetsData(std::ifstream& file, se::AssetData& asset);
		void SetRoadMap(const se::AssetData* asset, std::unordered_map<std::string, const se::AssetData*>& map);
		static void Clear();
		static void Update();
		Assets    m_Assets;
		AssetData m_AssetsData;
		RoadMap   m_RoadMap;
	};
}