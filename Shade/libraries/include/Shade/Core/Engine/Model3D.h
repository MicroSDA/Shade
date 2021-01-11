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
		Model3D(const std::string& fullClassName, const se::AssetData* data);
		virtual ~Model3D();
		virtual void Load() override;
		virtual void Init() override;
	private:
	};
}


