#pragma once
#pragma warning (disable:  4244) // const& warning
#include "Shade/Core/CoreAPI.h"
#include "Vendors/entt/entt.hpp"
#include "Shade/Core/Engine/Application.h"
#include "Shade/Core/Engine/AssetManager.h"
#include "Shade/Core/Engine/Shader.h"
#include "Shade/Core/Engine/Camera.h"
#include "Shade/Core/Engine/Timer.h"
#include "Shade/Core/Engine/EntitiesDocker.h"
#include "Shade/Core/Engine/FrameBuffer.h"
#include "Shade/Core/Util/Serializer.h"
#include "Shade/Core/Types.h"
#include "Shade/Core/Engine/Event.h"

namespace se
{
	template<typename T>
	using ShadeShared = std::shared_ptr<T>;

	class Layer;

	class SE_API Scene : public EntitiesDocker
	{
	public:
		friend class EventManager;
		friend class Application;

		Scene(const std::string& name);
		virtual ~Scene();
		const std::string& const GetName() { return m_Name; }

		se::ShadeShared<se::Camera> GetActiveCamera();
		void SetActiveCamera(const se::ShadeShared<se::Camera>& camera);
		inline       std::vector<se::Layer*>& GetLayers() { return m_Layers; };
		inline       se::Layer* GetLayer(const std::string& name);
		se::ShadeShared<se::FrameBuffer> GetFrameBuffer(const std::string& name);
		void CreateFrameBuffer(const std::string& name, const se::FramebufferSpec& spec);
	protected:
		virtual void OnCreate() = 0;
		virtual void OnInit() = 0;
		virtual void OnEvent(const se::Event& event) = 0;
		void         DeleteLayers();
		void         InitLayers();
		void         InitLayer(const std::string& name);
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

		void SetUpdate(const bool&  update);
		void SetRender(const bool&  render);
		void SetOnEvent(const bool& event);

		const bool& IsUpdate()  const;
		const bool& IsRender()  const;
		const bool& IsOnEvent() const;
	private:
		std::vector<se::Layer*> m_Layers;
		void         UpdateNativeScripts(const se::Timer& deltaTime);
		virtual void OnUpdate(const se::Timer& deltaTime) = 0;
		virtual void OnRender() = 0;
		virtual void OnDelete() = 0;
		se::ShadeShared<se::Camera> m_pMainCamera;
		bool						m_IsInitalized;
        std::unordered_map<std::string, se::ShadeShared<se::FrameBuffer>> m_FrameBuffers;
		bool m_IsUpdate  = true;
		bool m_IsRender  = true;
		bool m_IsOnEvent = true;
	};

}

