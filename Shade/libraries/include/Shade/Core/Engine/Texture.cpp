#include "stdafx.h"
#include "Texture.h"
#include "Shade/Core/Util/Binarizer.h"
#include "Vendors/SDL2/SDL.h"


se::Texture::Texture(const se::AssetData* data) : se::Asset(data),
	m_Texture(NULL)
{
}

se::Texture::~Texture()
{
	glDeleteTextures(1, &m_Texture);
}

void se::Texture::Bind(const GLuint& id)
{
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void se::Texture::UnBind()
{
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void se::Texture::Load()
{
	
	std::ifstream _File;
	_File.open(m_AssetData->_Path, std::ios::binary);

	if (_File.is_open())
	{
		std::string _Header = se::Binarizer::ReadNext<std::string>(_File);
		_Header.pop_back(); // remove \0;
		if (_Header == "#ShadeImage")
		{
			m_ImageData.m_Width = se::Binarizer::ReadNext<int>(_File);
			if(m_ImageData.m_Width < 1 || m_ImageData.m_Width > 10000)
				throw se::ShadeException(std::string("Wrong image width '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);

			m_ImageData.m_Height = se::Binarizer::ReadNext<int>(_File);
			if (m_ImageData.m_Height < 1 || m_ImageData.m_Height > 10000)
				throw se::ShadeException(std::string("Wrong image height '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);

			m_ImageData.m_HasAlpha = (se::Binarizer::ReadNext<int>(_File) == 4) ? true : false;
			m_ImageData.m_BufferSize = se::Binarizer::ReadNext<unsigned int>(_File);

			if (m_ImageData.m_BufferSize < 1 || m_ImageData.m_BufferSize > 104857600)
				throw se::ShadeException(std::string("Image size more then 100mb '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);

			m_ImageData.m_pImageData = new unsigned char[m_ImageData.m_BufferSize];
			_File.read(reinterpret_cast<char*>(m_ImageData.m_pImageData), m_ImageData.m_BufferSize);
			_File.close();
		}
		else
		{
			throw se::ShadeException(std::string("Wrong texture header '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);
		}
		
	}
	else
	{
		throw se::ShadeException(std::string("Failed to open image '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);
	}
}

void se::Texture::Init()
{
	if (m_ImageData.m_pImageData)
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (m_ImageData.m_HasAlpha)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ImageData.m_Width, m_ImageData.m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageData.m_pImageData);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ImageData.m_Width, m_ImageData.m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_ImageData.m_pImageData);
		}

		// Anisotropic filtering
		GLfloat _Anisotropic;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &_Anisotropic);
		if(_Anisotropic)
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, _Anisotropic);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);

		delete m_ImageData.m_pImageData;
	}
	else
	{
		throw se::ShadeException(std::string("Failed to initialize texure '"+ m_AssetData->_Path +"' image data is nullptr !").c_str(), se::SECode::Warning);
	}
	
}
