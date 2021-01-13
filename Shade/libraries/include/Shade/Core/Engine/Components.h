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

namespace se
{
	class Entity;

	struct ComponentBase
	{
		ComponentBase() = default;
		~ComponentBase() = default;
		virtual void OnCreate() {};
		virtual void OnDestroy() {};
	};

	struct TagComponent
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& other)
			:Tag(other)
		{
		}
	};
	struct CameraComponent : ComponentBase
	{
		se::Camera* Camera = nullptr;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(se::Camera* other)
			:Camera(other)
		{
		}
	};

	struct ShaderComponent : ComponentBase
	{
		se::Shader* Shader = nullptr;
		ShaderComponent() = default;
		~ShaderComponent()
		{
			se::AssetManager::Free(Shader->GetAssetData()->_Name);
		};
		ShaderComponent(const ShaderComponent&) = default;
		ShaderComponent(se::Shader* other)
			:Shader(other)
		{
			// Free asset data if it was hold
		};
	};

	struct Model3DComponent : ComponentBase
	{
		se::Model3D* Model3D = nullptr;
		Model3DComponent() = default;
		~Model3DComponent() 
		{
			if(Model3D) // Free if not nullptr
				se::AssetManager::Free(Model3D->GetAssetClassName());
		};
		Model3DComponent(se::Model3D* other)
			: Model3D(other) {}
		Model3DComponent(const Model3DComponent& other)
		{
			if (this != &other)
			{// Hold when it's copied 
				this->Model3D = other.Model3D;
				se::AssetManager::Hold<se::Model3D>(Model3D->GetAssetClassName());
			}	
		};
		Model3DComponent(Model3DComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Model3D = other.Model3D;
				other.Model3D = nullptr;
			}
		}
		Model3DComponent& operator=(const Model3DComponent& other)
		{
			this->Model3D = other.Model3D;
			se::AssetManager::Hold<se::Model3D>(Model3D->GetAssetClassName());
		}
		Model3DComponent& operator=(Model3DComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Model3D = other.Model3D;
				other.Model3D = nullptr;
			}
			return *this;
		}
	};

	struct TextureComponent : ComponentBase
	{
		se::Texture* Texture = nullptr;
		TextureComponent() = default;
		~TextureComponent()
		{
			if(Texture)
				se::AssetManager::Free(Texture->GetAssetClassName());
		};
		TextureComponent(se::Texture* other)
			: Texture(other) {};
		TextureComponent(const TextureComponent& other)
		{
			if (this != &other)
			{// Hold when it's copied 
				this->Texture = other.Texture;
				se::AssetManager::Hold<se::Texture>(Texture->GetAssetClassName());
			}
		};
		TextureComponent(TextureComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Texture = other.Texture;
				other.Texture = nullptr;
			}
		}
		TextureComponent& operator=(const TextureComponent& other)
		{
			this->Texture = other.Texture;
			se::AssetManager::Hold<se::Texture>(Texture->GetAssetClassName());
		}
		TextureComponent& operator=(TextureComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Texture = other.Texture;
				other.Texture = nullptr;
			}
			return *this;
		}
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

	struct NativeScriptComponent : ComponentBase
	{
		se::ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
	struct EnvironmentComponent : ComponentBase
	{
		se::Environment* Environment = nullptr;
		EnvironmentComponent() = default; // TODO light should be like asset ?
		EnvironmentComponent(const EnvironmentComponent&) = default;
		EnvironmentComponent(se::Environment* other)
			:Environment(other)
		{
		}
	};
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

}