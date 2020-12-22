#pragma once
#include "Shade/Core/CoreAPI.h"
//#include "Shade/Core/Engine/Vertex.h"
#include "Shade/Core/Engine/Drawable.h"
namespace se
{
	class SE_API Mesh :public se::Drawable
	{
	public:
		Mesh();
		~Mesh();
		void Draw();
	};
}
