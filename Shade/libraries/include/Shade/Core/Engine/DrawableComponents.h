#pragma once
#include "stdafx.h"
#include "Shade/Core/Engine/Mesh.h"
#include "Shade/Core/Engine/AssetManager.h"
#include "Shade/Core/Engine/Sprite.h"
#include "Shade/Core/Engine/Grid.h"

namespace se
{
	struct DrawableComponent
	{
		se::Drawable* Drawable = nullptr;
		DrawableComponent() = default;
		~DrawableComponent()
		{
			if (Drawable)
				delete Drawable;
		};
		DrawableComponent(se::Drawable* other) :
			Drawable(other) {}; // TODO how to resolve this ort just delete that construct
		DrawableComponent(const DrawableComponent& other)
		{
			if (this != &other)
			{
				this->Drawable = new se::Drawable;
				*this->Drawable = *other.Drawable;
			}
		};
		DrawableComponent(DrawableComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Drawable = other.Drawable;
				other.Drawable = nullptr;
			}
		};
		DrawableComponent& operator=(const DrawableComponent& other)
		{
			if (this != &other)
			{
				this->Drawable = new se::Drawable;
				*this->Drawable = *other.Drawable;
			}
			return *this;
		};
		DrawableComponent& operator=(DrawableComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Drawable = other.Drawable;
				other.Drawable = nullptr;
			}
			return *this;
		}
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

	//TODO Sprite constructs
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
