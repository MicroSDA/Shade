#pragma once
#include <Shade/Core/Render/Drawable.h>
#include <Shade/Core/Render/Vertex.h>
#include <Shade/Core/Asset/Asset.h>
#include <Shade/Core/Render/Camera.h>
#include <Shade/Utilities/Binarizer.h>

namespace se
{
	class SE_API Mesh : public se::Asset, public se::Drawable
	{

	public:	
		Mesh(const se::AssetData* data);
		virtual ~Mesh();
		// Унаследовано через Asset
		virtual void Load() override;
	private:
	};
}


