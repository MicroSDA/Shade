#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glad/glad.h"
#include "Vendors/glm/glm.hpp"
#include "Shade/Core/Engine/Texture.h"
#include "Shade/Core/Engine/AssetManager.h"
#include "Shade/Core/Engine/Vertex2D.h"
#include "Shade/Core/Engine/Font.h"

namespace se
{
	class SE_API Text
	{
	public:
		Text();
		virtual ~Text();
		void SetText(const std::string& text);
		const std::string& GetText() const;
		void Render();
		GLuint VAO, VBO;
	private:
		GLuint m_VAO, m_VBO, m_EBO;
		std::string m_Text;
		se::AssetPointer<se::Font> m_Font;
		GLuint m_BufferSize;
	};
}

