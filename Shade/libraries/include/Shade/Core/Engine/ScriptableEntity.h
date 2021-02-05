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
		friend struct NativeScriptComponent;

		virtual ~ScriptableEntity();
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
		void SetUpdate(const bool& isUpdate);
		const bool& IsUpdate() const;
	protected:
		virtual void OnCreate()  {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(const se::Timer& deltaTime) {}
		se::Entity   m_Entity;
	private:
		bool m_IsUpdate = false;
	};
}
