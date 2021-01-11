#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Vertex.h"
#include "Shade/Core/Engine/Drawable.h"
#include "Shade/Core/Engine/Texture.h"
#include "Shade/Core/Engine/Material.h"
#include "Shade/Core/Engine/EntitiesDocker.h"


namespace se
{
	class SE_API Mesh :public se::Asset, public se::Drawable, public se::EntitiesDocker
	{
	public:
		Mesh(const std::string& fullClassName, const se::AssetData* data);
		Mesh(const se::Mesh& other) :
			se::Asset(m_FullClassName, m_AssetData),
			m_Vertices(other.m_Vertices),
			m_Indices(other.m_Indices)
		{
			//TODO we should copy register some how
		}
		Mesh(se::Mesh&& other) noexcept :
			se::Asset(m_FullClassName, m_AssetData),
			m_Vertices(std::move(other.m_Vertices)),
			m_Indices(std::move(other.m_Indices))
		{
			//TODO we should move register some how
		}
		~Mesh();
		void SetVertices(std::vector<se::Vertex>& vertices);
		void SetIndices(std::vector<unsigned int>& indices);
		// Inherited via Asset
		virtual void Load() override;
		virtual void Init() override;
	private:
		std::vector<se::Vertex>   m_Vertices;
		std::vector<unsigned int> m_Indices;

	};
}
