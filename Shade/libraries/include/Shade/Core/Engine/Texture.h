#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Asset.h"
#include "Vendors/glad/glad.h"


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
		Texture(const std::string& fullClassName, const se::AssetData* data);
		virtual ~Texture();
		inline const void Bind(const uint32_t& id) const;
		static void UnBind(const uint32_t& id);
		const GLuint& GetTextureRenderId() const;
		// ������������ ����� Asset
		virtual void Load() override;
		virtual void Init() override;
	private:
		GLuint m_Texture;
		se::ImageData m_ImageData;

	};

}

