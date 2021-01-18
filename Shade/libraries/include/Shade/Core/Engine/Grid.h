#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"

namespace se
{
	class SE_API Grid : public se::Drawable
	{
	public:
		Grid(const float& width, const float& height, const int& density);
		~Grid();
		// Inherited via Drawable
		inline virtual const VertexBuffer& GetVertexBuffer() const override
		{
			return m_VertexBuffer;
		};
	private:
		float m_Width;
		float m_Height;
		int   m_CountWidth;
		int   m_CountHeight;

		std::vector<glm::fvec3>  m_Vertices;
		std::vector<glm::uvec4>  m_Indices;
		se::VertexBuffer         m_VertexBuffer;
	
	};

};