#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Vertex.h"
#include "Shade/Core/Engine/Drawable.h"

namespace se
{
	class SE_API Mesh :public se::Drawable
	{
	public:
		Mesh(std::vector<se::Vertex>& vertices, std::vector<unsigned int>& indices);
		~Mesh();
	private:
		std::vector<se::Vertex>   m_Vertices;
		std::vector<unsigned int> m_Indices;
	};
}
