#pragma once
#include <core/Definitions.h>
#include <core/events/EventManager.h>
#include <utilities/Log.h>
#include <string>

namespace se {

	enum class SE_API SceneState
	{
		Continue,
		PreviousScene,
		NextScene,
		Exit
	};

	class SE_API Scene
	{
	public:
		Scene();
		Scene(const std::string& name);
		virtual ~Scene();
		virtual void OnCreate() const = 0;
		virtual SceneState OnUpdate() const = 0;
		virtual void OnRender()  const = 0;
		virtual void  OnPause()  const = 0;
		virtual void  OnResume() const = 0;
		virtual void  OnDelete() const = 0;

		inline void SetName(const std::string& name) { m_Name = name; }
		inline std::string GetName() const  { return m_Name; }
	protected:
		std::string  m_Name;
		mutable SceneState   m_State;
	};
}

