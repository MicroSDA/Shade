#pragma once
#include "Shade/Core/Engine/Entity.h"
#include "Shade/Core/Engine/Timer.h"
#include "Shade/Core/Engine/Application.h"

namespace se
{
	class SE_API ScriptableEntity
	{
	public:

		friend class Scene;

		virtual ~ScriptableEntity();
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	protected:
		virtual void OnCreate()  {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(const se::Timer& deltaTime) {}
		se::Entity   m_Entity;
	private:
	};
}
