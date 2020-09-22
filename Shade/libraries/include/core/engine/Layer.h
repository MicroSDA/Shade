#pragma once
#include <Definitions.h>
#include <core/render/Render.h>

#include <string>
namespace se 
{
	class SE_API Layer
	{
		using EventCallback = std::function<bool(Event const&)>;
	public:
		Layer(const std::string& name, const void* scene);
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
		const void* m_Scene;
	};
}


