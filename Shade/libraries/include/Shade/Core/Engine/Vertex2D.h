#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glm/glm.hpp"

#include <vector>
namespace se
{
	class SE_API Vertex2D
	{
	public:
		Vertex2D();
		Vertex2D(const glm::vec2& position, const glm::vec2& textureCoords);
		Vertex2D(const float& positionX, const float& positionY,
			const float& textureCoordX,
			const float& textureCoordY);
		~Vertex2D();

		glm::vec2 m_Position;
		glm::vec2 m_TextureCoords;
	};
}

