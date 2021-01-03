#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Vertex.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Texture.h"

namespace se
{
	class SE_API Mesh :public se::Drawable
	{
	public:
		Mesh(std::vector<se::Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<se::Texture*>& textures);
		~Mesh();
		void TexturesBind();
		void TexturesUnBind();
		virtual void Init() override;
	private:
		std::vector<se::Vertex>   m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<se::Texture*> m_Textures;
	};
}
