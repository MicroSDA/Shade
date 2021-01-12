#include "stdafx.h"
#include "Sprite.h"

se::Sprite::Sprite(): se::Drawable()
{
	m_DrawMode = se::DrawMode::TRIANGLE_STRIP;
	m_AttribCount = 1; // DO NOT FORGET //
}

se::Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

void se::Sprite::Init()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Quad), &m_Quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);
}