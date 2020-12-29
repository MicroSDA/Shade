#pragma once
#include "stdafx.h"
#include "Shade/Core/Engine/Transform.h"
#include "Shade/Core/Engine/Model3D.h"
#include "Shade/Core/Engine/Mesh.h"
#include "Shade/Core/Engine/Camera.h"
#include "Shade/Core/Engine/Texture.h"
#include "Shade/Core/Engine/ScriptableEntity.h"

namespace se
{
	class Entity;

	struct TransformComponent
	{
		se::Transform Transform;
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const se::Transform& other)
			:Transform(other)
		{
		}
		operator se::Transform& () { return Transform; }
		operator const se::Transform& () const { return Transform; }
	};
	
	struct CameraComponent
	{
		se::Camera* Camera = nullptr;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(se::Camera* other)
			:Camera(other)
		{
		}
	};

	struct ShaderComponent
	{
		se::Shader* Shader = nullptr;
		ShaderComponent() = default;
		ShaderComponent(const ShaderComponent&) = default;
		ShaderComponent(se::Shader* other)
			:Shader(other)
		{
		}
	};

	struct Model3DComponent
	{
		se::Model3D* Model3D = nullptr;

		Model3DComponent() = default;
		Model3DComponent(const Model3DComponent&) = default;
		Model3DComponent(se::Model3D* other)
			:Model3D(other)
		{
		}
	};

	struct TextureComponent
	{
		se::Texture* Texture = nullptr;

		TextureComponent() = default;
		TextureComponent(const TextureComponent&) = default;
		TextureComponent(se::Texture* other)
			:Texture(other)
		{
		}
	};
	struct RenderComponent
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

	struct NativeScriptComponent
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
}