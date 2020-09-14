#include "Scene.h"

se::Scene::Scene()
	:m_Name("Undefined Scene"), m_State(SceneState::Continue)
{
	DEBUG_LOG("Scene(" + m_Name + ")", LOG_LEVEL::INFO_SECONDARY);
}

se::Scene::Scene(const std::string& name)
	:m_Name(name), m_State(SceneState::Continue)
{
	DEBUG_LOG("Scene(" + m_Name + ")", LOG_LEVEL::INFO_SECONDARY);
}

se::Scene::~Scene()
{
	DEBUG_LOG("~Scene(" + m_Name + ")", LOG_LEVEL::INFO_SECONDARY);
}
