#pragma once
#include "stdafx.h"
#include "Shade/Core/Engine/Transform3D.h"
#include "Shade/Core/Engine/Transform2D.h"

namespace se
{
	struct Transform2DComponent
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

	struct Transform3DComponent
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

}
