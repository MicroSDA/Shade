#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Entity.h"

namespace se
{
	class Scene;

	class SE_API Serializer
	{
	public:
		static bool SerializeScene(const std::string& filepath,   se::Scene& scene);
		static bool DeserializeScene(const std::string& filepath, se::Scene& scene);
	private:

	};
}


