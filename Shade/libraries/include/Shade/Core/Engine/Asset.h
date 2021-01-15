#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/AssetData.h"
#include "Shade/Core/Util/ShadeException.h"

namespace se
{
	// Based on std::shared_ptr, using for asstes and AssetManager
	template<typename T>
	using AssetPointer = std::shared_ptr<T>;
	// Based on std::weak_ptr, using for asstes and AssetManager
	template<typename T>
	using AssetPointerWeak = std::weak_ptr<T>;

	class SE_API Asset
	{
	public:
		Asset(const std::string& fullClassName, const se::AssetData* data); // ??
		virtual ~Asset();
		virtual void Load() = 0;
		virtual void Init() = 0;
		const se::AssetData* GetAssetData() const;
		std::string          GetAssetClassName() const;
	protected:
		const se::AssetData* m_AssetData;
		const std::string    m_FullClassName;
		bool m_IsInitialized;
	private:
	};
}


