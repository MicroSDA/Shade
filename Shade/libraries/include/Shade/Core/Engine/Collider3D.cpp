#include "stdafx.h"
#include "Collider3D.h"

se::Collider3D::Collider3D(const se::Collider3D::Type& type) :
	m_Type(type)
{
}

const se::Collider3D::Type& se::Collider3D::GetType() const
{
	return m_Type;
}