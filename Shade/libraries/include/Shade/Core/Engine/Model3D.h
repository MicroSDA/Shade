#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Asset.h"
#include "Shade/Core/Engine/Mesh.h"

namespace se
{
	class SE_API Model3D : public se::Asset
	{
	public:
		Model3D(const se::AssetData* data);
		~Model3D();
		std::vector<se::Mesh> m_Meshes; // Temp here as public

		virtual void Load() override;
		virtual void Init() override;
	private:
	};
}


