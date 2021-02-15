#include "stdafx.h"
#include "Environment.h"
#include "Shade/Core/Util/Log.h"

se::Environment::Environment(const Environment::Type& type) :
	m_Type(type)
{
}

se::Environment::~Environment()
{
}

const se::Environment::Type& se::Environment::GetType() const
{
	return m_Type;
}
