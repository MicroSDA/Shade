#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/entt/entt.hpp"

namespace se
{
	class Entity;

	class SE_API EntitiesDocker
	{
	public:
		EntitiesDocker() = default;
		virtual ~EntitiesDocker();

		se::Entity CreateEntity(const std::string& name = "Entity");
	
		void DestroyEntity(const Entity& entity);
		void DestroyEntities();
		entt::registry& GetEntities();
	private:
		entt::registry     m_Registry;
	};
}

