#include "stdafx.h"
#include "Model3D.h"

se::Model3D::Model3D(const se::AssetData* data) :se::Asset(data)
{
}

se::Model3D::~Model3D()
{
}

void se::Model3D::Load()
{

	m_Meshes.emplace_back();
}
