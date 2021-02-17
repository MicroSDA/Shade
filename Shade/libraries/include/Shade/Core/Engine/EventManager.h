#pragma once
#include "Shade/Core/Util/Log.h"
#include "Shade/Core/Engine/Input.h"
#include "Shade/Core/Engine/Event.h"

namespace se
{
	// Forward Declaration
	class Layer;
	class Scene;
	//////////////////////
	class SE_API EventManager
	{
		
	public:
		friend class Application;
		static void PusEvent(const se::Event& event);
	private:
		//Singleton implementation
		EventManager();
		~EventManager();
		EventManager(const EventManager&) = delete;
		EventManager& operator= (const EventManager&) = delete;
		EventManager(const EventManager&&) = delete;
		EventManager& operator= (const EventManager&&) = delete;
		static EventManager& Get();
		/////////////////////////////////

		void Update();
	};
}


