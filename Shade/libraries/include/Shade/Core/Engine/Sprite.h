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
		inline virtual const VertexBuffer& GetVertexBuffer() const
		{
			return m_VertexBuffer;
		}
	protected:
		static GLfloat m_Quad[];
		static se::VertexBuffer m_VertexBuffer;
	private:
	};

}

