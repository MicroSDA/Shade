#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Asset.h"
#include "Vendors/glad/glad.h"
#include "Shade/Core/Engine/Shader.h"

namespace se
{
	struct ImageData
	{
		unsigned char* m_pImageData = nullptr;
		unsigned int   m_BufferSize = 0;
		int            m_Width      = 0;
		int            m_Height     = 0;
		int            m_InternalFormat = 3; // RGB by default
	};

	class SE_API Texture : public se::Asset
	{
	public:
		Texture();
		virtual ~Texture();
		const void Bind(const se::Shader* shader, const std::uint32_t& id) const;
		static void UnBind(const uint32_t& id);
		const GLuint& GetTextureRenderId() const;
		// ������������ ����� Asset
		virtual void LoadFromAssetData(const std::string& assetId, se::AssetData& data) override;
		virtual void Init() override;
	protected:
		GLuint m_Texture;
		se::ImageData m_ImageData;

	};

}

