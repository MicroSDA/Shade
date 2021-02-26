#include "stdafx.h"
#include "Texture.h"
#include "Shade/Core/Util/Binarizer.h"

se::Texture::Texture() :
	m_Texture(NULL)
{
}

se::Texture::~Texture()
{
	glDeleteTextures(1, &m_Texture);
}

inline const void se::Texture::Bind(const uint32_t& id) const
{
	glActiveTexture(GL_TEXTURE0 + static_cast<GLuint>(id));
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void se::Texture::UnBind(const uint32_t& id)
{
	glActiveTexture(GL_TEXTURE0 + static_cast<GLuint>(id));
	glBindTexture(GL_TEXTURE_2D, 0);
}

const GLuint& se::Texture::GetTextureRenderId() const
{
	return m_Texture;
}

void se::Texture::LoadFromAssetData(const std::string& assetId, se::AssetData& data)
{
	m_AssetId   = assetId;
	m_AssetData = &data;

	std::ifstream _File;
	_File.open(m_AssetData->Path, std::ios::binary);

	if (_File.is_open())
	{
		std::string _Header = se::Binarizer::ReadNext<std::string>(_File);
		_Header.pop_back(); // remove \0;
		if (_Header == "#ShadeImage")
		{
			m_ImageData.m_Width = se::Binarizer::ReadNext<int>(_File);
			if (m_ImageData.m_Width < 1 || m_ImageData.m_Width > 10000)
				throw se::ShadeException(std::string("Wrong image width '" + m_AssetData->Path + "' !").c_str(), se::SECode::Warning);

			m_ImageData.m_Height = se::Binarizer::ReadNext<int>(_File);
			if (m_ImageData.m_Height < 1 || m_ImageData.m_Height > 10000)
				throw se::ShadeException(std::string("Wrong image height '" + m_AssetData->Path + "' !").c_str(), se::SECode::Warning);

			m_ImageData.m_InternalFormat = se::Binarizer::ReadNext<int>(_File);
			m_ImageData.m_BufferSize = se::Binarizer::ReadNext<unsigned int>(_File);

			if (m_ImageData.m_BufferSize < 1 || m_ImageData.m_BufferSize > 104857600)
				throw se::ShadeException(std::string("Image size more then 100mb '" + m_AssetData->Path + "' !").c_str(), se::SECode::Warning);

			m_ImageData.m_pImageData = new unsigned char[m_ImageData.m_BufferSize];
			_File.read(reinterpret_cast<char*>(m_ImageData.m_pImageData), m_ImageData.m_BufferSize);
			_File.close();
		}
		else
		{
			throw se::ShadeException(std::string("Wrong texture header '" + m_AssetData->Path + "' !").c_str(), se::SECode::Warning);
		}

	}
	else
	{
		throw se::ShadeException(std::string("Failed to open image '" + m_AssetData->Path + "' !").c_str(), se::SECode::Warning);
	}
}

void se::Texture::Init()
{
	if(!m_IsInitialized)
	{ 
		if (m_ImageData.m_pImageData)
		{
			GLint _InternalFormat = 0;

			// If texture has gray scale or something else, can thorw an exeption, so keep it in mind
			switch (m_ImageData.m_InternalFormat)
			{
				case 1:
					_InternalFormat = GL_RED;
					break;
				case 2:
					_InternalFormat = GL_RG;
					break;
				case 3:
					_InternalFormat = GL_RGB;
					break;
				case 4:
					_InternalFormat = GL_RGBA;
					break;
				default:
					throw se::ShadeException(std::string("Unsupported texture format in '" + m_AssetData->Path + "'!").c_str(), se::SECode::Warning);
					break;
			}

			glGenTextures(1, &m_Texture);
			glBindTexture(GL_TEXTURE_2D, m_Texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, _InternalFormat, m_ImageData.m_Width, m_ImageData.m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageData.m_pImageData);
		
			// Anisotropic filtering
			GLfloat _Anisotropic;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &_Anisotropic);
			if(_Anisotropic)
				//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, _Anisotropic);

			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);

			glBindTexture(GL_TEXTURE_2D, 0);
			delete[] m_ImageData.m_pImageData;
			m_ImageData.m_pImageData = nullptr;
			m_IsInitialized = true;
		}
		else
		{
			throw se::ShadeException(std::string("Failed to initialize texure '" + m_AssetData->Path + "' image data is nullptr !").c_str(), se::SECode::Warning);
		}

	}
	else
	{
		throw se::ShadeException(std::string("Asset has been already initialized'" + m_AssetData->Path + "'").c_str(), se::SECode::Warning);
	}
}
