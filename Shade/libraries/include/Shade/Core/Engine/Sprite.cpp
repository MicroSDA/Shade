#include "stdafx.h"
#include "Sprite.h"
#include "Shade/Core/Engine/Components.h"

GLfloat se::Sprite::m_Quad[8] = { -1.0,1.0,  -1.0,-1.0,  1.0,1.0,  1.0,-1.0 };
se::VertexBuffer se::Sprite::m_VertexBuffer;

se::Sprite::Sprite(const std::string& fullClassName, const se::AssetData* data): se::Asset(fullClassName, data), se::Drawable()
{
	m_DrawMode = se::DrawMode::TRIANGLE_STRIP;
	m_DrawCount = 4; 
}

se::Sprite::~Sprite()
{

}

void se::Sprite::Init()
{
	if (!m_IsInitialized)
	{   // Check if it was already initiailized
		// Sprite must have one static buffer, cause there's same geometry for all
		if (m_VertexBuffer.GetVAO() == NULL)
		{
			m_VertexBuffer = se::VertexBuffer::Create<GLfloat>(
				{ {se::VertexBufferElementType::Float2, "Position"} },
				&m_Quad[0], 8);
		}
		
		for (auto& _Asset : m_AssetData->_Dependency)
		{
			if (_Asset._Type == se::AssetDataType::Texture)
			{
				auto _TextureEntity = this->CreateEntity();
				_TextureEntity.AddComponent<se::TextureComponent>(
					se::AssetManager::Hold<se::Texture>(m_FullClassName + "." + _Asset._Name));
			}
		}
		
		m_IsInitialized = true;
	}
	else
	{
		throw se::ShadeException(std::string("Asset has been already initialized'" + m_AssetData->_Path + "'").c_str(), se::SECode::Warning);
	}

}

void se::Sprite::Load()
{
	
}

