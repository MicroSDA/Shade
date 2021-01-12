#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Vertex.h"

namespace se
{
	class SE_API Grid : public se::Drawable
	{
	public:
		Grid(const float& width, const float& height, const int& densit);
		~Grid();
	private:
		float m_Width;
		float m_Height;
		int   m_CountWidth;
		int   m_CountHeight;

		std::vector<glm::fvec3>   m_Vertices;
		std::vector<glm::uvec4> m_Indices;
	};

};