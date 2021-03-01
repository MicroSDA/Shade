#pragma once
#include "Shade/Core/Engine/Asset.h"
#include "Shade/Core/Util/Binarizer.h"
#include "Shade/Core/Util/ShadeException.h"
#include "Shade/Core/Util/Log.h"

namespace se
{  
	// Manager for loading and manage asset data
	class SE_API AssetManager
	{
		// Struct for placing one of two pointer types
		struct AssetReferences
		{
			std::variant<se::AssetPointerWeak<se::Asset>, se::AssetPointer<se::Asset>> m_Ref;
		};

		using ID			= std::string;
		using Assets        = std::unordered_map<ID, AssetReferences>;
		using AssetDataList = std::unordered_map<ID, const se::AssetData*>;
	public:
		friend class Application;
		friend class Asset;
		// Use for loading new asset into memeory by specific asset class name.
		// If you want to kepp an asset in memeory even if all holders was deleted, 
		// use tru as second parametr or false if you don't want to keep it in memeory.
		// All assets that were held with the false flag will be removed automatically !
		template<typename T>
		static se::AssetPointer<T> Hold(const ID& className, const se::Asset::Flag& flag = se::Asset::Flag::None);
		// Unload specific asset if ref count is 0
		static void Free(const std::string& className);
		static void WriteAssetDataList(const std::string& filePath, const se::AssetData& asset);
		static void ReadAssetDataList(const std::string& filePath);
		static const AssetData& GetAssetDataList();
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
		void WriteAssetDataListRecursively(std::ofstream& file, const se::AssetData& asset);
		// Internal use for asset object only, will remove entry from AssetData map
		static void ImLast(const std::string& assetId) ;
		void ReadAssetsData(std::ifstream& file, se::AssetData& asset);
		void SetRoadMap(const se::AssetData* asset, std::unordered_map<std::string, const se::AssetData*>& map);
		// Internal use for Application only
		static void Clear();
		Assets			m_Assets;
		AssetData		m_AssetsData;
		AssetDataList   m_AssetDataList;

		bool m_ImDestructing = false;
	};
	template<typename T>
	inline se::AssetPointer<T> AssetManager::Hold(const ID& className, const se::Asset::Flag& flag)
	{
		auto& _Instance = GetInstance();
		// Trying to find in Assets map
		auto _AElement = _Instance.m_Assets.find(className);
		if (_AElement != _Instance.m_Assets.end())
		{
			// If already loaded
			// Check if asset with false flag
			if (std::get_if<se::AssetPointerWeak<se::Asset>>(&_AElement->second.m_Ref))
			{
				auto& _Weak = std::get<se::AssetPointerWeak<se::Asset>>(_AElement->second.m_Ref);
				// If nobody links
				if (_Weak.expired())
				{   // Then asset has been removed
					goto load_new;
				}
				else
				{   // Check if asset has correct type
					auto _pAsset = static_cast<T*>(_Weak.lock().get()); // TODO keep it in mind

					if (_pAsset)
					{
						se::AssetPointer<se::Asset> _Out;
						// Convert from week no shared
						_Out = std::get<se::AssetPointerWeak<se::Asset>>(_AElement->second.m_Ref).lock();
						// Return our pointer
						return se::AssetPointer<T>(std::static_pointer_cast<T>(_Out));
					}
					else
					{
						std::string _Msg("Error: Wrong asset assignment :'" + className + "'");
						throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
					}

				}

			}// Check if asset with true flag
			else if (std::get_if<se::AssetPointer<se::Asset>>(&_AElement->second.m_Ref))
			{
				// Check if asset has correct type
				auto _pAsset = dynamic_cast<T*>(std::get<se::AssetPointer<se::Asset>>(_AElement->second.m_Ref).get());
				if (_pAsset)
				{   // Return our poiter
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
			auto _RElement = _Instance.m_AssetDataList.find(className);
			if (_RElement != _Instance.m_AssetDataList.end())
			{
				// Loading asset
				auto _Asset = new T();
				if (_Asset)
				{
					_Asset->LoadFromAssetData(_RElement->first, const_cast<se::AssetData&>(*_RElement->second));
					_Asset->Init(); // Temporary here 
					se::AssetPointer<se::Asset> _Out(_Asset);
					if (flag == se::Asset::Flag::KeepAlive)
					{
						// Can be placed as usually
						_Instance.m_Assets.emplace(std::pair<ID, AssetReferences>(className, AssetReferences{ _Out }));
					}
					else
					{   // Cannot be placed as usually need to convert to weak
						_Instance.m_Assets.emplace(std::pair<ID, AssetReferences>(className, AssetReferences{ se::AssetPointerWeak<se::Asset>(_Out) }));
					}

					return se::AssetPointer<T>(std::static_pointer_cast<T>(_Out));
				}
				else
				{
					std::string _Msg("Error: Wrong asset assignment :'" + className + "'");
					throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
				}

			}
			else
			{
				SE_DEBUG_PRINT("Specifaed class name '" + className + "' hasn't been found", se::SLCode::Warning);
				//std::string _Msg("Exeption : Specifaed class name '" + className + "' hasn't been found");
				//throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
				return nullptr;
			}

			SE_DEBUG_PRINT("Specifaed class name '" + className + "' hasn't been found", se::SLCode::Warning);
			//std::string _Msg("Exeption : Specifaed class name '" + className + "' hasn't been found");
			//throw se::ShadeException(_Msg.c_str(), se::SECode::Error);
			return nullptr;
		}

		return nullptr; // for warning disable
	}
}