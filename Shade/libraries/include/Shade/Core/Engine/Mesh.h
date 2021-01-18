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
		virtual ~Mesh();
		void SetVertices(std::vector<se::Vertex>& vertices);
		void SetIndices(std::vector<unsigned int>& indices);
		// Inherited via Asset
		virtual void Load() override;
		virtual void Init() override;
		// Inherited via Drawable
		inline virtual const VertexBuffer& GetVertexBuffer() const override
		{
			return m_VertexBuffer;
		};
	private:
		std::vector<se::Vertex>   m_Vertices;
		std::vector<unsigned int> m_Indices;
		se::VertexBuffer          m_VertexBuffer;
	};
}
