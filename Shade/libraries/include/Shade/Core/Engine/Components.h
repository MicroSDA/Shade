#pragma once
#include "stdafx.h"
#include "Shade/Core/Engine/Transform.h"
#include "Shade/Core/Engine/Model3D.h"
#include "Shade/Core/Engine/Mesh.h"
#include "Shade/Core/Engine/Camera.h"

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
	};

	struct ShaderComponent
	{
		se::Shader* Shader = nullptr;
	};

	struct Model3DComponent
	{
		se::Model3D* Model3D = nullptr;
	};

	struct RenderComponent
	{
		void(*Layout)(se::Entity);
	};
}