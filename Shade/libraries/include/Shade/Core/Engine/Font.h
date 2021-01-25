#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Texture.h"
#include "Shade/Core/Engine/AssetManager.h"

namespace se
{
	struct FontCharData
	{
		int AsciiCode = -1;
		float Xpos = 0, Ypos = 0;
		float Width = 0.0f, Height = 0.0f;
		float Xoffset = 0.0f, Yoffset = 0.0f;
		float Xadvance = 0.0f;
	};

	class SE_API Font : public se::Asset
	{
	public:
		Font(const std::string& fullClassName, const se::AssetData* data);
		virtual ~Font();
		// Inherited via Asset
		virtual void Load() override;
		virtual void Init() override;
		const se::FontCharData& GetCharData(const char& character) const;
		const se::Texture* GetAtlas() const;
	private:
		mutable std::unordered_map<char, se::FontCharData> m_FontData;
		se::AssetPointer<se::Texture>                      m_Atlas;
	};
}

