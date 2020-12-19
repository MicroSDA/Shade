#pragma once
#include <Shade/Definitions.h>
#include <Shade/Utilities/Types.h>
#include <Shade/Core/Render/Render.h>
#include <Shade/Core/Render/Shader.h>
#include <Shade/Core/Render/Mesh.h>
#include <Shade/Core/Render/Camera.h>
#include <Shade/Core/Engine/Entity.h>
#include <Shade/Core/Engine/Scene.h>

#include <string>

namespace se 
{
	
	class SE_API Layer
	{
		using EventCallback = std::function<bool(Event const&)>;
	public:
		Layer(const std::string& name, se::Scene* scene);
		virtual ~Layer();
		virtual void OnCreate() = 0;
		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0; //TODO:Delta as args
		virtual void OnRender() = 0; //TODO:Delta as args
		virtual void OnDelete() = 0;

		void RegisterEventCallback(const EventType& type, const EventCallback& callback);
		inline std::string GetName() const { return m_Name; }
	private:
		std::string m_Name;
	protected:
		se::Scene* m_pScene;
	};
}


