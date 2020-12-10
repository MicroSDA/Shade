#pragma once
#include <Definitions.h>
#include <iostream>

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
	
	/*constexpr AssetDataType& operator +=(AssetDataType& left, const AssetDataType right) noexcept
	{
		return left;
	}*/
	
	enum class AssetDataSubType
	{
		None,
		Diffuse,
		Specular,
		NormalMap,
		Vertex,
		Fragment,
		Geometry
	};
	struct SE_API AssetData
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

