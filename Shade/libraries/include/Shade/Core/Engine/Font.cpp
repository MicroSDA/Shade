#include "stdafx.h"
#include "Font.h"

se::Font::Font(const std::string& fullClassName, const se::AssetData* data) : se::Asset(fullClassName, data)
{

}

se::Font::~Font()
{
}

void se::Font::Load()
{
	std::ifstream _FontFile;
	_FontFile.open(m_AssetData->_Path, std::ios::binary);
	if (_FontFile.is_open())
	{
		std::string _Header = se::Binarizer::ReadNext<std::string>(_FontFile);
		_Header.pop_back(); // remove \0;
		if (_Header == "#ShadeFont")
		{
			m_FontData.m_TileWidth = se::Binarizer::ReadNext<int>(_FontFile);
			m_FontData.m_TileHeight = se::Binarizer::ReadNext<int>(_FontFile);

			int _CharsCount = se::Binarizer::ReadNext<int>(_FontFile);
			if (_CharsCount && _CharsCount < 1000)
			{
				for (auto i = 0; i < _CharsCount; i++)
				{
					se::CharData _Char;
					_Char.AsciiCode = se::Binarizer::ReadNext<int>(_FontFile);
					_Char.Xpos = se::Binarizer::ReadNext<float>(_FontFile);
					_Char.Ypos = se::Binarizer::ReadNext<float>(_FontFile);
					_Char.Width = se::Binarizer::ReadNext<float>(_FontFile);
					_Char.Height = se::Binarizer::ReadNext<float>(_FontFile);
					_Char.Xoffset = se::Binarizer::ReadNext<float>(_FontFile);
					_Char.Yoffset = se::Binarizer::ReadNext<float>(_FontFile);
					_Char.Xadvance = se::Binarizer::ReadNext<float>(_FontFile);
					m_FontData.CharsData[char(_Char.AsciiCode)] = _Char;
				}

				m_ImageData.m_Width = se::Binarizer::ReadNext<int>(_FontFile);
				if (m_ImageData.m_Width < 1 || m_ImageData.m_Width > 10000)
					throw se::ShadeException(std::string("Wrong image width '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);

				m_ImageData.m_Height = se::Binarizer::ReadNext<int>(_FontFile);
				if (m_ImageData.m_Height < 1 || m_ImageData.m_Height > 10000)
					throw se::ShadeException(std::string("Wrong image height '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);

				m_ImageData.m_InternalFormat = se::Binarizer::ReadNext<int>(_FontFile);
				m_ImageData.m_BufferSize = se::Binarizer::ReadNext<unsigned int>(_FontFile);

				if (m_ImageData.m_BufferSize < 1 || m_ImageData.m_BufferSize > 104857600)
					throw se::ShadeException(std::string("Image size more then 100mb '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);

				m_ImageData.m_pImageData = new unsigned char[m_ImageData.m_BufferSize];
				_FontFile.read(reinterpret_cast<char*>(m_ImageData.m_pImageData), m_ImageData.m_BufferSize);
			}
			else
			{
				std::cout << "Chars limit\n";
			}

		}
		
		_FontFile.close();
	}
	std::string   _Node;
}

void se::Font::Init()
{
	if (!m_IsInitialized)
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
				throw se::ShadeException(std::string("Unsupported texture format in '" + m_AssetData->_Path + "'!").c_str(), se::SECode::Warning);
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
			if (_Anisotropic)
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
			throw se::ShadeException(std::string("Failed to initialize texure '" + m_AssetData->_Path + "' image data is nullptr !").c_str(), se::SECode::Warning);
		}

	}
	else
	{
		throw se::ShadeException(std::string("Asset has been already initialized'" + m_AssetData->_Path + "'").c_str(), se::SECode::Warning);
	}
}

const se::FontData& se::Font::GetFontData() const
{
	return m_FontData;
}

const GLuint& se::Font::GetAtlas() const
{
	return m_Texture;
}
