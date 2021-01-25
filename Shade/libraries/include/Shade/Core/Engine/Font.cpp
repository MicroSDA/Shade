#include "stdafx.h"
#include "Font.h"

se::Font::Font(const std::string& fullClassName, const se::AssetData* data) : se::Asset(fullClassName, data)
{
	std::ifstream _FontFile("./project/resources/fonts/candara/candara.fnt");
	std::string   _Node;

	while (!_FontFile.eof())
	{
		_FontFile >> _Node;
		if (_Node == "char")
		{
			se::FontCharData _CharData;
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
			m_FontData[char(_CharData.AsciiCode)] = _CharData;
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

const se::FontCharData& se::Font::GetCharData(const char& character) const
{
	return m_FontData[character];
}

const se::Texture* se::Font::GetAtlas() const
{
	return m_Atlas.get();
}
