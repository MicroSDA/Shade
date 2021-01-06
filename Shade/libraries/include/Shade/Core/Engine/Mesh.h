#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Vertex.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Texture.h"
#include "Shade/Core/Engine/Material.h"

namespace se
{
	class SE_API Mesh :public se::Drawable
	{
	public:
		Mesh(const std::vector<se::Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<se::Texture*>& textures, const se::Material& material);
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
