#pragma once
#include "stdafx.h"
#include "Shade/Core/Engine/TransformComponents.h"
#include "Shade/Core/Engine/DrawableComponents.h"
#include "Shade/Core/Engine/Model3D.h"
#include "Shade/Core/Engine/Camera.h"
#include "Shade/Core/Engine/Texture.h"
#include "Shade/Core/Engine/ScriptableEntity.h"
#include "Shade/Core/Engine/GeneralLight.h"
#include "Shade/Core/Engine/PointLight.h"
#include "Shade/Core/Engine/SpotLight.h"
#include "Shade/Core/Engine/Material.h"
#include "Shade/Core/Engine/Font.h"
#include "Shade/Core/Engine/Text.h"
#include "Shade/Core/Engine/FrameBuffer.h"
#include "Shade/Core/Engine/RigidBody3D.h"

namespace se
{
	class Entity;

	// Base component, isn't using now
	struct ComponentBase
	{
		ComponentBase() = default;
		~ComponentBase() = default;
		//virtual void OnCreate() {};
		//virtual void OnDestroy() {};
	};
	// Use when you want to name a specific entity
	// Will be added automatically when an entity is being created
	// Default value for Tag is 'Entity'
	struct TagComponent : se::ComponentBase
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& other)
			:Tag(other)
		{
		}
		operator std::string& () { return Tag; }
		operator const std::string& () const { return Tag; }

		operator char* () { return Tag.data(); }
		operator const char* () const { return Tag.c_str(); }
	};
	struct CameraComponent : ComponentBase
	{
		// Set shared i guess TODO
		se::ShadeShared<se::Camera> Camera;
		bool IsPrimary = false;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const se::ShadeShared<se::Camera>& other)
			:Camera(other)
		{
		}
		CameraComponent(se::Camera* camera) // Disable this becouse we need to pas only shared pointer
			:Camera(se::ShadeShared<se::Camera>(camera))
		{
		}

	};
	
	struct Model3DComponent : ComponentBase
	{
		se::AssetPointer<se::Model3D> Model3D;
		Model3DComponent() = default;
		~Model3DComponent() = default;
		Model3DComponent(const se::AssetPointer<se::Model3D>& other)
			: Model3D(other) {};
		Model3DComponent(se::Model3D* other)
			: Model3D(se::AssetPointer<se::Model3D>(other)) {};
		Model3DComponent(const Model3DComponent&) = default;
	};

	struct TextureComponent : ComponentBase
	{
		se::AssetPointer<se::Texture> Texture;
		TextureComponent() = default;
		~TextureComponent() = default;
		TextureComponent(const se::AssetPointer<se::Texture>& other)
			: Texture(other) {};
		TextureComponent(const TextureComponent&) = default;
	};
	struct RenderComponent : ComponentBase
	{
		using RenderComponentCallback = void(*)(se::Entity);
		RenderComponentCallback Callback;

		RenderComponent() = default;
		RenderComponent(const RenderComponent&) = default;
		RenderComponent(const RenderComponentCallback& other)
			:Callback(other)
		{
		}
		operator RenderComponentCallback& () { return Callback; }
		operator const RenderComponentCallback& () const { return Callback; }
	};

	// Use for binding controller to an entity, cannot be copied, only move semantic is available
	// Deleting automatically when Scene is destructing or manually by calling GetEntities()->destroy or Get Entities()->remove
	// Do not call delete * directly neither for component nor controller.
	struct NativeScriptComponent : ComponentBase
	{
		friend class se::Scene;
		friend class se::Application;

		se::ScriptableEntity* Instance = nullptr;
		// Copy constructor and assigment were deleted 
		NativeScriptComponent() = default;
		NativeScriptComponent(const NativeScriptComponent&) = delete;
		NativeScriptComponent& operator=(const NativeScriptComponent& other) = delete;
		// Move constructor
		NativeScriptComponent(NativeScriptComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Instance = other.Instance;
				other.Instance = nullptr;

				this->InstantiateScript = other.InstantiateScript;
				other.InstantiateScript = nullptr;

				this->DestroyScript = other.DestroyScript;
				other.DestroyScript = nullptr;
			}
		}
		// Move assigment
		NativeScriptComponent& operator=(NativeScriptComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Instance = other.Instance;
				other.Instance = nullptr;

				this->InstantiateScript = other.InstantiateScript;
				other.InstantiateScript = nullptr;

				this->DestroyScript = other.DestroyScript;
				other.DestroyScript = nullptr;
			}
			return *this;
		};
		// Call only when entity is destructing by GetEntites()->destroy or GetEntites()->remove
		~NativeScriptComponent()
		{
			if (Instance != nullptr)
			{
				Instance->OnDestroy();
				DestroyScript(this);
			}
				
		}
		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	private:
		ScriptableEntity* (*InstantiateScript)()	  = nullptr;
		void (*DestroyScript)(NativeScriptComponent*) = nullptr;

	};
	// Use for Environment pointer, shouldn't be deleted manually, based on the se::ShadeShared which use std::shared_ptr
	struct EnvironmentComponent : ComponentBase
	{
		se::ShadeShared<se::Environment> Environment;
		EnvironmentComponent() = default; // TODO light should be like asset ?
		// Default copy
		EnvironmentComponent(const EnvironmentComponent&) = default;
		EnvironmentComponent& operator=(const EnvironmentComponent&) = default;
		EnvironmentComponent(const se::ShadeShared<se::Environment>& other)
			:Environment(other)	{}

	};
	struct GeneralLightComponent : ComponentBase
	{
		se::ShadeShared<se::GeneralLight> Light;
		GeneralLightComponent() = default; 
		// Default copy
		GeneralLightComponent(const GeneralLightComponent&) = default;
		GeneralLightComponent& operator=(const GeneralLightComponent&) = default;
		GeneralLightComponent(se::GeneralLight* other)
			:Light(other) {}
		GeneralLightComponent(const se::ShadeShared<se::GeneralLight>&other)
			:Light(other) {}
	};
	struct PointLightComponent : ComponentBase
	{
		se::ShadeShared<se::PointLight> Light;
		PointLightComponent() = default;
		// Default copy
		PointLightComponent(const PointLightComponent&) = default;
		PointLightComponent& operator=(const PointLightComponent&) = default;
		PointLightComponent(se::PointLight* other)
			:Light(other) {}
		PointLightComponent(const se::ShadeShared<se::PointLight>& other)
			:Light(other) {}
	};
	struct SpotLightComponent : ComponentBase
	{
		se::ShadeShared<se::SpotLight> Light;
		SpotLightComponent() = default;
		// Default copy
		SpotLightComponent(const SpotLightComponent&) = default;
		SpotLightComponent& operator=(const SpotLightComponent&) = default;
		SpotLightComponent(se::SpotLight* other)
			:Light(other) {}
		SpotLightComponent(const se::ShadeShared<se::SpotLight>& other)
			:Light(other) {}
	};
	// Base lighting material, usually being used by se::Mesh as entity
	struct MaterialComponent : ComponentBase
	{
		se::Material Material;
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		MaterialComponent(const se::Material& other)
			:Material(other)
		{
		}
		operator se::Material& () { return Material; }
		operator const se::Material& () const { return Material; }
	};

	struct FontComponent : ComponentBase
	{
		se::AssetPointer<se::Font> Font;
		FontComponent() = default;
		~FontComponent() = default;
		FontComponent(const se::AssetPointer<se::Font>& other)
			: Font(other) {};
		FontComponent(const FontComponent&) = default;
	};

	struct DrawableTextComponent : ComponentBase
	{
		se::ShadeShared<se::Text> Text;
		DrawableTextComponent() = default;
		~DrawableTextComponent() = default;
		DrawableTextComponent(const se::ShadeShared<se::Text>& other) //  TODO Nedd to create copy constructor for vertex buffer
			: Text(other) {};
		DrawableTextComponent(const DrawableTextComponent&) = default;
	};

	struct FrameBufferComponent : ComponentBase
	{
		se::ShadeShared<se::FrameBuffer> FrameBuffer;
		FrameBufferComponent() = default;
		~FrameBufferComponent() = default;
		FrameBufferComponent(const se::ShadeShared<se::FrameBuffer>& other) //  TODO Nedd to create copy constructor for vertex buffer
			: FrameBuffer(other) {};
		FrameBufferComponent(const FrameBufferComponent&) = default;
	};

	struct RigidBody3DComponent
	{
		se::RigidBody3D Body;
		RigidBody3DComponent() = default;
		~RigidBody3DComponent() = default;
		RigidBody3DComponent(const se::RigidBody3D& other)
			: Body(other) {};
		RigidBody3DComponent(const RigidBody3DComponent&) = default;
	};
}