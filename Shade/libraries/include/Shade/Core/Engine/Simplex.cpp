#include "stdafx.h"
#include "Simplex.h"

se::Simplex::Simplex() : m_Points(
	{
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f)
	}), m_Count(0)
{}
void se::Simplex::push_front(const glm::vec3& point)
{
	m_Points = { point, m_Points[0], m_Points[1], m_Points[2] };
	m_Count = std::min(m_Count + 1, 4u);
}
