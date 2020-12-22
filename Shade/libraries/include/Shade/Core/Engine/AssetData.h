#pragma once
#include "stdafx.h"

namespace se
{
	enum class AssetDataType
	{
		Container,
		Packet,
		Model3D,
		Mesh,
		Texture,
		Shader
	};
	enum class AssetDataSubType
	{
		None,
		Diffuse,
		Specular,
		NormalMap,
	};
	struct AssetData
	{
		std::string             _Name;
		AssetDataType           _Type;
		AssetDataSubType        _SubType;
		std::string             _Path;
		long long               _Offset = NULL;
		std::vector<AssetData>  _Dependency;
		AssetData*              _Parrent = nullptr;
	};
};


/*constexpr AssetDataType& operator +=(AssetDataType& left, const AssetDataType right) noexcept
{
	return left;
}*/
