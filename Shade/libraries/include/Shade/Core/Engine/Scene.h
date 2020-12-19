#pragma once
#include <Shade/Utilities/Log.h>
#include <Shade/Vendors/glad/glad.h>
#include <Shade/Vendors/entt/entt.hpp>
#include <Shade/Utilities/Types.h>

#include <functional>
#include <vector>



namespace se
{
	
	enum class SceneState
	{
		CONTINUE,
		STOP,
		NEXTSCENE,
		PREVIOUSSCENE
	};

	class Entity;
	class Layer;

	class SE_API Scene
	{
		using EventCallback = std::function<bool(Event const&)>;
	public:
		Scene(const std::string& name);
		virtual ~Scene();

		virtual void  OnCreate() = 0;
		virtual void  OnInit()   = 0;
		virtual SceneState OnUpdate() = 0; // TODO: delta as args
		virtual void  OnRender() = 0;
		virtual void  OnDelete() = 0;

		inline std::string GetName() { return m_Name; }
		void SetScene(const std::string& name);

		Entity CreateEntity();
		entt::registry  m_Registry;
		//Layer GetCurrentLayer();
		//virtual void OnChange() = 0; Probably	
	protected:
		void RegisterEventCallback(const EventType& type, const EventCallback& callback);
		void AddLayer(Layer* layer);
		std::vector<Layer*> m_Layers;
	private:
		std::string     m_Name;
		//void SetScene(const std::string& name);
	};
}


