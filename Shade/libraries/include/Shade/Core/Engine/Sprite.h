#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Texture.h"

namespace se
{
	static class SE_API Sprite :public se::Drawable
	{
	public:
		Sprite();
		virtual ~Sprite();
		void Init();
	protected:
		const se::Texture* m_Texture;
		static const GLfloat      m_Quad[];
	private:
	};

}

