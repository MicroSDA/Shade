#include "Drawable.h"
#include <iostream>


se::Drawable::Drawable():
	m_VAO(NULL),
	m_AttribCount(NULL),
	m_IndicesCount(NULL),
	m_DrawMode(DrawMode::TRIANGLES)
{

}

se::Drawable::~Drawable()
{
}
