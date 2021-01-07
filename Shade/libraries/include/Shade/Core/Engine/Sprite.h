#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Texture.h"

namespace se
{
	class SE_API Sprite : public se::Drawable
	{
	public:
		Sprite();
		virtual ~Sprite();
		void SetTexture(const se::Texture* texture);
		const se::Texture* GetTexture() const;
		virtual void Init() override;
	protected:
		const se::Texture* m_Texture;
		const GLfloat m_Quad[8] =
		{ 
		  -1.0,1.0,  -1.0,-1.0,
		   1.0,1.0,   1.0,-1.0 
		};
	private:
	};

}

