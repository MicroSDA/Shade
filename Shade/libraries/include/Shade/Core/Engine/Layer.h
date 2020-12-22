#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/EventManager.h"
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Engine/Scene.h"
#include "Shade/Core/Engine/Entity.h"
#include "Shade/Core/Engine/Components.h"
#include "Vendors/glad/glad.h"

namespace se
{
	//class Scene;

	class SE_API Layer
	{
	public:
		Layer(const std::string& name, se::Scene* scene);
		virtual ~Layer();

		virtual void OnCreate() = 0;
		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0; //TODO:Delta as args
		virtual void OnRender() = 0; //TODO:Delta as args
		virtual void OnDelete() = 0;

		se::Scene* GetScene() { return m_pScene; }

		const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
	private:
		se::Scene* m_pScene;

	};

}
