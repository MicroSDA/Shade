#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Asset.h"
#include "Shade/Core/Engine/EntitiesDocker.h"

namespace se
{
	class SE_API Sprite :public se::Asset, public se::Drawable, public se::EntitiesDocker
	{
	public:
		Sprite(const std::string& fullClassName, const se::AssetData* data);
		virtual ~Sprite();
		virtual void Load() override;
		virtual void Init() override;
	protected:
		const GLfloat m_Quad[8] = { -1.0,1.0,  -1.0,-1.0,  1.0,1.0,  1.0,-1.0 };
	private:
	};

}

