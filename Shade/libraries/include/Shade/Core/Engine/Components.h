#pragma once
#include "stdafx.h"
#include "Shade/Core/Engine/Transform3D.h"
#include "Shade/Core/Engine/Transform2D.h"
#include "Shade/Core/Engine/Model3D.h"
#include "Shade/Core/Engine/Mesh.h"
#include "Shade/Core/Engine/Camera.h"
#include "Shade/Core/Engine/Texture.h"
#include "Shade/Core/Engine/ScriptableEntity.h"
#include "Shade/Core/Engine/GeneralLight.h"
#include "Shade/Core/Engine/PointLight.h"
#include "Shade/Core/Engine/SpotLight.h"
#include "Shade/Core/Engine/Material.h"
#include "Shade/Core/Engine/Sprite.h"

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

	struct Transform3DComponent : ComponentBase
	{
		se::Transform3D Transform;
		Transform3DComponent() = default;
		~Transform3DComponent() = default;

		Transform3DComponent(const Transform3DComponent&) = default;
		Transform3DComponent(const se::Transform3D& other)
			:Transform(other)
		{
		}
		operator se::Transform3D& () { return Transform; }
		operator const se::Transform3D& () const { return Transform; }
	};
	struct Transform2DComponent : ComponentBase
	{
		se::Transform2D Transform;
		Transform2DComponent() = default;
		Transform2DComponent(const Transform2DComponent&) = default;
		Transform2DComponent(const se::Transform2D& other)
			:Transform(other)
		{
		}
		operator se::Transform2D& () { return Transform; }
		operator const se::Transform2D& () const { return Transform; }
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

	struct MeshComponent : ComponentBase
	{
		se::Mesh* Mesh = nullptr;
		MeshComponent() = default;
		~MeshComponent()
		{
			if (Mesh)
				se::AssetManager::Free(Mesh->GetAssetClassName());
		};
		MeshComponent(se::Mesh* other)
			:Mesh(other) {};
		MeshComponent(const MeshComponent& other)
		{
			if (this != &other)
			{
				this->Mesh = other.Mesh;
				se::AssetManager::Hold<se::Mesh>(Mesh->GetAssetClassName());
			}
		};
		MeshComponent(MeshComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Mesh = other.Mesh;
				other.Mesh = nullptr;
			}
		};
		MeshComponent& operator=(const MeshComponent& other)
		{ 
			this->Mesh = other.Mesh;
			se::AssetManager::Hold<se::Mesh>(Mesh->GetAssetClassName());
		};
		MeshComponent& operator=(MeshComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Mesh = other.Mesh;
				other.Mesh = nullptr;
			}
			return *this;
		}
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
		se::Environment* Instance = nullptr;
		EnvironmentComponent() = default; // TODO light should be like asset ?
		EnvironmentComponent(const EnvironmentComponent&) = default;
		EnvironmentComponent(se::Environment* other)
			:Instance(other)
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

	struct SpriteComponent : ComponentBase
	{
		se::Sprite* Sprite = nullptr;
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(se::Sprite* other)
			:Sprite(other)
		{
		}
	};
}