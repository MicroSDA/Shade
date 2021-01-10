#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/entt/entt.hpp"
#include "Shade/Core/Engine/Application.h"
#include "Shade/Core/Engine/AssetManager.h"
#include "Shade/Core/Engine/Shader.h"
#include "Shade/Core/Engine/Camera.h"
#include "Shade/Core/Engine/Timer.h"
#include "Shade/Core/Engine/EntitiesDocker.h"
//#include "Shade/Core/Engine/Layer.h"
//#include "Shade/Core/Engine/Entity.h"

namespace se
{
	class Layer;

	class SE_API Scene : public EntitiesDocker
	{
	public:
		friend class Application;

		Scene(const std::string& name);
		virtual ~Scene();
		const std::string& const GetName() { return m_Name; }

		se::Camera* GetMainCamera();
		void SetMainCamera(se::Camera* camera);
	protected:
		virtual void OnCreate() = 0;
		virtual void OnInit() = 0;
		void         UpdateNativeScripts(const se::Timer& deltaTime);
		void         DeleteLayers();
		void         InitLayers();
		void         InitLayer(const std::string& name);
		inline       std::vector<se::Layer*>& GetLayers() { return m_Layers; };
		template<typename T>
		se::Layer* CreateLayer(const std::string& name)
		{
			auto _Layer = static_cast<se::Layer*>(new T(name, this));
			_Layer->OnCreate();

			SE_DEBUG_PRINT((std::string("Layer: '") + name + "' has been created!").c_str(), se::SLCode::InfoSecondary);

			m_Layers.push_back(_Layer);
			return _Layer;
		}

		std::string    m_Name;
	private:
		std::vector<se::Layer*> m_Layers;
		virtual void OnUpdate(const se::Timer& deltaTime) = 0;
		virtual void OnRender() = 0;
		virtual void OnDelete() = 0;
		se::Camera* m_pMainCamera;
		bool m_IsInitalized;
	};

}

