#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glad/glad.h"
#include "Vendors/glm/glm.hpp"
#include "Shade/Core/Engine/Texture.h"
#include "Shade/Core/Engine/AssetManager.h"
#include "Shade/Core/Engine/Vertex2D.h"
#include "Shade/Core/Engine/Font.h"
#include "Shade/Core/Engine/Drawable.h"

namespace se
{
	class SE_API Text : public se::Drawable
	{
	public:
		Text();
		virtual ~Text();

		void SetText(const std::string& text);
		const std::string& GetText() const;
		void SetFont(const se::AssetPointer<se::Font>& font);
		const se::AssetPointer<se::Font>& GetFont() const;
		// Inherited via Drawable
		virtual const VertexBuffer& GetVertexBuffer() const override;
	private:
		se::AssetPointer<se::Font> m_Font;
		se::VertexBuffer           m_VertexBuffer;
		std::string                m_Text;
		int                        m_BufferedCharCount;
	};
}

