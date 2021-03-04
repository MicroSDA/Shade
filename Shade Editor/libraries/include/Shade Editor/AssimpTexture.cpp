#include "AssimpTexture.h"
#include <Shade/Core/Util/Binarizer.h>
#include "Vendors/stbi/stb_image.h"

void AssimpTexture::LoadFromFile(const char* filePath)
{
	int _Width, _Height, _Channels;
	unsigned char* _Data = stbi_load(filePath, &_Width, &_Height, &_Channels, STBI_rgb_alpha);

	if (_Data)
	{
		m_ImageData.m_Height			= _Height;
		m_ImageData.m_Width				= _Width;
		m_ImageData.m_InternalFormat	= _Channels;
		m_ImageData.m_pImageData		= _Data;
		m_ImageData.m_BufferSize		= sizeof(_Data);
		//stbi_image_free(_Data);
	}
	else
	{
		throw se::ShadeException(std::string("Failed to open source image AssimTexture' !").c_str(), se::SECode::Warning);
	}
}

void AssimpTexture::SetImportedAssetData(const se::AssetData* data)
{
	m_ImportedAssetData = *data;
	SetAssetData(m_ImportedAssetData);
}
