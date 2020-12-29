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
		bool           m_HasAlpha   = false;
	};

	class SE_API Texture : public se::Asset
	{
	public:
		Texture(const se::AssetData* data);
		~Texture();
		void Bind(const GLuint& id);
		static void UnBind();
		// Унаследовано через Asset
		virtual void Load() override;
		virtual void Init() override;
	private:
		GLuint m_Texture;
		se::ImageData m_ImageData;

	};

}

