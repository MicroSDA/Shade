#pragma once
#include "stdafx.h"
#include "Shade/Core/Engine/Mesh.h"
#include "Shade/Core/Engine/AssetManager.h"
#include "Shade/Core/Engine/Sprite.h"
#include "Shade/Core/Engine/Grid.h"

namespace se
{
	// Use when you cannot manage life for specific object, see std::shared_ptr
	template<typename T>
	using ShadeShared = std::shared_ptr<T>;

	struct DrawableComponent
	{
		ShadeShared<Drawable> Drawable;
		DrawableComponent() = default;
		~DrawableComponent() = default;
		DrawableComponent(const DrawableComponent&) = default;
		DrawableComponent(const ShadeShared<se::Drawable>& other)
			:Drawable(other) {};
	};

	struct MeshComponent
	{
		se::AssetPointer<se::Mesh> Mesh;
		MeshComponent() = default;
		~MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(const se::AssetPointer<se::Mesh>& other)
			:Mesh(other) {};
	};
	struct SpriteComponent
	{
		se::AssetPointer<se::Sprite> Sprite;
		SpriteComponent() = default;
		~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const se::AssetPointer<se::Sprite>& other)
			:Sprite(other) {};
	};
}
