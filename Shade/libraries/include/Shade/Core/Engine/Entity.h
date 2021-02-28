#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/entt/entt.hpp"
#include "Shade/Core/Engine/EntitiesDocker.h"
#include "Shade/Core/Util/ShadeException.h"
#include "Shade/Core/Util/Log.h"
namespace se
{
	class SE_API Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, se::EntitiesDocker* docker);
		Entity(const Entity& other) : 
			m_EntityHandle(other.m_EntityHandle),
			m_pDocker(other.m_pDocker)
		{ }
		~Entity();
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
				throw se::ShadeException(std::string("Entity already has component! : " + std::string(typeid(T).name())).c_str(), se::SECode::Error);
			return m_pDocker->GetEntities().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}
		template<typename T>
		T& GetComponent() const
		{
			//GetMy if you want to create in tour registry
			if (!HasComponent<T>())
				throw se::ShadeException(std::string("Entity does not have component! : " + std::string(typeid(T).name())).c_str(), se::SECode::Error);
			return m_pDocker->GetEntities().get<T>(m_EntityHandle);
		}
		template<typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>())
				throw se::ShadeException(std::string("Entity does not have component! : " + std::string(typeid(T).name())).c_str(), se::SECode::Error);
			m_pDocker->GetEntities().remove<T>(m_EntityHandle);
		}
		template<typename T>
		bool HasComponent() const
		{
			return m_pDocker->GetEntities().has<T>(m_EntityHandle);
		}
		bool IsValid();
		void Destroy();
		se::EntitiesDocker& GetDocker();
		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_pDocker == other.m_pDocker;
		}
		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
		friend std::string operator+(const std::string& string, const Entity& other)
		{
			return std::string(string + std::to_string(static_cast<uint32_t>(other.m_EntityHandle)));
		}
		operator std::string () { return std::to_string(static_cast<uint32_t>(m_EntityHandle)); }
		operator const std::string () const { return std::to_string(static_cast<uint32_t>(m_EntityHandle)); }
	private:
		entt::entity m_EntityHandle { entt::null };
		se::EntitiesDocker* m_pDocker = nullptr;
	};

}
