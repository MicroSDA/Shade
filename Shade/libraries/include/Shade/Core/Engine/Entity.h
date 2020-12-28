#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/entt/entt.hpp"
#include "Shade/Core/Engine/Scene.h"

namespace se
{

	class SE_API Entity
	{
	public:
		Entity(entt::entity handle, se::Scene* scene);
		/*Entity(const Entity& other) : 
			m_EntityHandle(other.m_EntityHandle),
			m_pScene(other.m_pScene)
		{ }*/
		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
				throw se::ShadeException("Entity already has component!", se::SECode::Error);
			return m_pScene->GetRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent() const
		{
			if (!HasComponent<T>())
				throw se::ShadeException("Entity does not have component!", se::SECode::Error);
			return m_pScene->GetRegistry().get<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>())
				throw se::ShadeException("Entity does not have component!", se::SECode::Error);
			m_pScene->GetRegistry().remove<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_pScene->GetRegistry().has<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_pScene == other.m_pScene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity m_EntityHandle{ entt::null };
		se::Scene* m_pScene = nullptr;
	};
}
