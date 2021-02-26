#pragma once
#include "stdafx.h"

namespace se
{
	// Specify your asset according to the Asset Data structure
	struct SE_API AssetData
	{
		std::string						ID      = "ROOT";							// Asset Id
		std::string						Path    = "";								// Path to file
		std::uint32_t					Offset  = 0;
		enum class AType : uint32_t
		{
			Container,
			Packet,
			Shader,
			Model3D,
			Mesh,
			Texture,
			Material,
			Sprite,
			Font

		}		Type    = se::AssetData::AType::Container;	// Type
		enum class ASubType : uint32_t
		{
			None,
			Diffuse,
			Specular,
			NormalMap,
			Albedo
			//TODO: More

		}	SubType = se::AssetData::ASubType::None;    // Sub type
		std::vector<AssetData>			Childs;										// Childs
		se::AssetData* Parrent	= nullptr;
		se::AssetData* Ally		= nullptr;											// Isn't implemented yeat
	};
};


/*constexpr AssetDataType& operator +=(AssetDataType& left, const AssetDataType right) noexcept
{
	return left;
}*/
