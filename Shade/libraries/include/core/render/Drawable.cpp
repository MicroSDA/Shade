#include "Drawable.h"
#include <iostream>


se::Drawable::Drawable():
	m_VAO(NULL),
	m_AttribCount(NULL),
	m_IndicesCount(NULL),
	m_DrawMode(DrawMode::TRINAGES)
{
	GLfloat vertex[] = { -1.0f, -1.0f,  0.0f, 1.0f,  1.0f, -1.0f };
}

se::Drawable::~Drawable()
{
}
