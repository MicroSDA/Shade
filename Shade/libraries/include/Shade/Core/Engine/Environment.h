#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Timer.h"
#include "Shade/Core/Engine/Shader.h"

namespace se
{
	class SE_API Environment
	{
	public:
		enum class Type : uint32_t
		{
			Environment,
			GeneralLight,
			PointLight,
			SpotLight
		};
		Environment(const Environment::Type& type);
		virtual ~Environment();
		virtual void OnUpdate(const se::Timer& deltaTime) = 0;
		virtual void Process(const se::Shader* shader) = 0;
		const Environment::Type& GetType() const ;
	protected:
		const Environment::Type m_Type;
	private:
	};

}

