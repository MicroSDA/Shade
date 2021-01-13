#include "stdafx.h"
#include "Sprite.h"
#include "Shade/Core/Engine/Components.h"

se::Sprite::Sprite(const std::string& fullClassName, const se::AssetData* data): se::Asset(fullClassName, data), se::Drawable()
{
	m_DrawMode = se::DrawMode::TRIANGLE_STRIP;
	m_AttribCount = 1; // DO NOT FORGET //
	m_IndicesCount = 4; // DO NOT FORGET //
}

se::Sprite::~Sprite()
{

}

void se::Sprite::Init()
{
	if (!m_IsInitialized)
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Quad), &m_Quad, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindVertexArray(0);

		for (auto& _Asset : m_AssetData->_Dependency)
		{
			if (_Asset._Type == se::AssetDataType::Texture)
			{
				auto _TextureEntity = this->CreateEntity();
				_TextureEntity.AddComponent<se::TextureComponent>(
					se::AssetManager::Hold<se::Texture>(m_FullClassName + "." + _Asset._Name));
			}
			

		}
		
	}
	else
	{
		throw se::ShadeException(std::string("Asset has been already initialized'" + m_AssetData->_Path + "'").c_str(), se::SECode::Warning);
	}

}

void se::Sprite::Load()
{
	
}
