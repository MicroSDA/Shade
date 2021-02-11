#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Texture.h"
#include "Shade/Core/Engine/AssetManager.h"

namespace se
{
	struct CharData
	{
		int AsciiCode   = -1;
		float Xpos      = 0,    Ypos       = 0;
		float Width     = 0.0f, Height     = 0.0f;
		float Xoffset   = 0.0f, Yoffset    = 0.0f;
		float Xadvance  = 0.0f;	
	};
	struct FontData
	{
		mutable std::unordered_map<char, se::CharData> CharsData;
		float m_TileWidth = 0.0f, m_TileHeight = 0.0f;
	};

	class SE_API Font : public se::Asset
	{
	public:
		Font();
		virtual ~Font();
		// Inherited via Asset
		virtual void LoadFromAssetData(const std::string& assetId, se::AssetData& data) override;
		virtual void Init() override;
		const se::FontData& GetFontData() const;
		const GLuint& GetAtlas() const;
	private:
		GLuint                        m_Texture;
		FontData                      m_FontData;
		se::ImageData                 m_ImageData;
	};
}


