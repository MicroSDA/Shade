#include "stdafx.h"
#include "ScriptableEntity.h"

se::ScriptableEntity::~ScriptableEntity()
{
	std::string _Msg = "ScriptableEntity id: " + std::to_string((unsigned int)m_Entity) + " has been destroyed";
	SE_DEBUG_PRINT(_Msg.c_str(), se::SLCode::InfoSecondary);
}

void se::ScriptableEntity::SetUpdate(const bool& isUpdate)
{
	m_IsUpdate = isUpdate;
}

const bool& se::ScriptableEntity::IsUpdate() const
{
	return m_IsUpdate;
}
