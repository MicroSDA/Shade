#include "stdafx.h"
#include "Font.h"

se::Font::Font(const std::string& fullClassName, const se::AssetData* data) : se::Asset(fullClassName, data)
{
	std::ifstream _FontFile("./project/resources/fonts/candara/candara.fnt");
	std::string   _Node;

	while (!_FontFile.eof())
	{
		_FontFile >> _Node;
		if (_Node.find("scaleW") != _Node.npos)
			m_FontData.m_TileWidth = std::atoi(_Node.erase(0, 7).c_str());

		if (_Node.find("scaleH") != _Node.npos)
			m_FontData.m_TileHeight = std::atoi(_Node.erase(0, 7).c_str());

		if (_Node.find("file") != _Node.npos)
		{
			size_t first = _Node.find_first_of("\"") + 1;
			size_t last = _Node.find_last_of("\"");
			std::cout << _Node.substr(first, last - first) << std::endl; // TODO Need to laod it from file, move to sierizliaer whole font code
		}
			
		
		if (_Node == "char")
		{
			se::CharData _CharData;
			_FontFile >> _Node;
			_CharData.AsciiCode = std::atoi(_Node.erase(0, 3).c_str()); // id= 
			_FontFile >> _Node;
			_CharData.Xpos = std::atof(_Node.erase(0, 2).c_str()); // x=
			_FontFile >> _Node;
			_CharData.Ypos = std::atof(_Node.erase(0, 2).c_str()); // y=
			_FontFile >> _Node;
			_CharData.Width = std::atof(_Node.erase(0, 6).c_str()); // width=
			_FontFile >> _Node;
			_CharData.Height = std::atof(_Node.erase(0, 7).c_str()); // height=
			_FontFile >> _Node;
			_CharData.Xoffset = std::atof(_Node.erase(0, 8).c_str()); // xoffset=
			_FontFile >> _Node;
			_CharData.Yoffset = std::atof(_Node.erase(0, 8).c_str()); // yoffset=
			_FontFile >> _Node;
			_CharData.Xadvance = std::atof(_Node.erase(0, 9).c_str()); // xadvance=
			m_FontData.CharsData[char(_CharData.AsciiCode)] = _CharData;
		}
	}

	_FontFile.close();

	m_Atlas = se::AssetManager::Hold<se::Texture>("Font");
}

se::Font::~Font()
{
}

void se::Font::Load()
{
}

void se::Font::Init()
{
}

const se::FontData& se::Font::GetFontData() const
{
	return m_FontData;
}

const se::Texture* se::Font::GetAtlas() const
{
	return m_Atlas.get();
}
