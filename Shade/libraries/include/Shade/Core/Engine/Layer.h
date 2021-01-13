#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/EventManager.h"
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Engine/Scene.h"
#include "Shade/Core/Engine/Entity.h"
#include "Shade/Core/Engine/Components.h"
//#include "Vendors/glad/glad.h"
#include "Shade/Core/Engine/Renderer.h"
#include "Shade/Core/Engine/Controllers.h"
#include "Shade/Core/Engine/Timer.h"

namespace se
{
	//class Scene;

	class SE_API Layer
	{
	public:
		friend class Scene;
		Layer(const std::string& name, se::Scene* scene);
		virtual ~Layer();

		virtual void OnCreate() = 0;
		virtual void OnInit() = 0;
		//TODO Move to private and friend class
		virtual void OnUpdate(const se::Timer& deltaTime) = 0; //TODO:Delta as args
		virtual void OnRender() = 0;
		virtual void OnDelete() = 0;
		void SetActive(const bool& isActive);
		void SetEventsUpdate(const bool& isEventUpdate);
		void SetRender(const bool& isRender);
		void SetUpdate(const bool& isUpdate);

		const bool& IsActive() const;
		const bool& IsEventsUpdating() const;
		const bool& IsRendering() const;
		const bool& IsUpdating() const;

		se::Scene* GetScene() { return m_pScene; }
		const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
	private:
		se::Scene* m_pScene;
		bool m_IsActive       = true;
		bool m_IsEventsUpdate = true;
		bool m_IsRender       = true;
		bool m_IsUpdate       = true;
		bool m_IsInitalized   = false;
	};

}
