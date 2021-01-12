#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Texture.h"

namespace se
{
	class SE_API Sprite :public se::Drawable
	{
	public:
		Sprite();
		virtual ~Sprite();
		void Init();
	protected:
		const GLfloat m_Quad[8] = { -1.0,1.0,  -1.0,-1.0,  1.0,1.0,  1.0,-1.0 };
	private:
	};

}

