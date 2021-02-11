#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Asset.h"
#include "Shade/Core/Engine/Mesh.h"
#include "Shade/Core/Engine/EntitiesDocker.h"

namespace se
{
	class SE_API Model3D : public se::Asset , public se::EntitiesDocker
	{
	public:
		Model3D();
		virtual ~Model3D();
		virtual void LoadFromAssetData(const std::string& assetId, se::AssetData& data) override;
		virtual void Init() override;
	private:
	};
}


