#pragma once
#include <Shade/Core/Render/Transform.h>
#include <Shade/Core/Render/Shader.h>
#include <Shade/Core/Render/Mesh.h>
#include <Shade/Core/Render/Camera.h>
namespace se
{
	class Entity;
	struct TransformComponent
	{
		se::Transform Transform;
		TransformComponent() = default;
		TransformComponent(const TransformComponent& ) = default;
		TransformComponent(const se::Transform& other)
			:Transform(other)
		{
		}
		operator se::Transform& () { return Transform; }
		operator const se::Transform& () const { return Transform; }
	};

	struct ShaderComponent
	{
		const se::Shader* Shader;
		ShaderComponent() = default;
		ShaderComponent(const ShaderComponent&) = default;
		operator const se::Shader& () const { return *Shader; }
	};

	struct MeshComponent
	{
		const se::Mesh* Mesh;
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		operator const se::Mesh& () const { return *Mesh; }
	};

	struct RenderLayoutComponent
	{
		void(*Layout)(se::Entity&);
		RenderLayoutComponent() = default;
		RenderLayoutComponent(const RenderLayoutComponent&) = default;
	};

	struct CameraComponent
	{
		se::Camera* Camera;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		operator se::Camera& () { return *Camera; }
	};
}

