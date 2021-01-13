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

	//TODO Sprite constructs
	struct SpriteComponent
	{
		se::Sprite* Sprite = nullptr;
		SpriteComponent() = default;
		~SpriteComponent()
		{
			if (Sprite)
				se::AssetManager::Free(Sprite->GetAssetClassName());
		};
		SpriteComponent(se::Sprite* other)
			:Sprite(other) {};
		SpriteComponent(const SpriteComponent& other)
		{
			if (this != &other)
			{
				this->Sprite = other.Sprite;
				se::AssetManager::Hold<se::Sprite>(Sprite->GetAssetClassName());
			}
		};
		SpriteComponent(SpriteComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Sprite = other.Sprite;
				other.Sprite = nullptr;
			}
		};
		SpriteComponent& operator=(const SpriteComponent& other)
		{
			this->Sprite = other.Sprite;
			se::AssetManager::Hold<se::Sprite>(Sprite->GetAssetClassName());
		};
		SpriteComponent& operator=(SpriteComponent&& other) noexcept
		{
			if (this != &other)
			{
				this->Sprite = other.Sprite;
				other.Sprite = nullptr;
			}
			return *this;
		}
	};
}
