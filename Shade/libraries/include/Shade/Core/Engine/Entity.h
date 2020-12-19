#pragma once
#include <Shade/Core/Engine/Scene.h>
#include <Shade/Vendors/entt/entt.hpp>
#include <Shade/Core/Engine/Components.h>

namespace se
{
	class SE_API Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, se::Scene* scene);
		~Entity();

		template<typename T>
		bool HasComponent()
		{
			return m_pScene->m_Registry.has<T>(m_EntityHandl);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
			{
#ifdef SE_DEBUG
				DEBUG_PRINT("Error: Entity already has component", LogLevel::ERROR);
#else 
				DEBUG_SAVE("Error: Entity already has component", LogLevel::ERROR);
#endif // SE_DEBUG
				exit(-1);
			}

			return m_pScene->m_Registry.emplace<T>(m_EntityHandl, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			if (!HasComponent<T>())
			{
#ifdef SE_DEBUG
				DEBUG_PRINT("Error: Entity does not have component", LogLevel::ERROR);
#else 
				DEBUG_SAVE("Error: Entity does not have component", LogLevel::ERROR);
#endif // SE_DEBUG
				exit(-1);
			}

			return m_pScene->m_Registry.get<T>(m_EntityHandl);
		}

		template<typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>())
			{
#ifdef SE_DEBUG
				DEBUG_PRINT("Error: Entity does not have component", LogLevel::ERROR);
#else 
				DEBUG_SAVE("Error: Entity does not have component", LogLevel::ERROR);
#endif // SE_DEBUG
				exit(-1);
			}

			m_pScene->m_Registry.remove<T>(m_EntityHandl);
		}
	private:
		entt::entity m_EntityHandl{ 0 };
		se::Scene* m_pScene = nullptr;
	};

}
