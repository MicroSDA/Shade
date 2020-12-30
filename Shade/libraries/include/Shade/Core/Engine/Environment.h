#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Timer.h"
#include "Shade/Core/Engine/Shader.h"

namespace se
{
	class SE_API Environment
	{
	public:
		Environment();
		virtual ~Environment();
		virtual void OnUpdate(const se::Timer& deltaTime) = 0;
		virtual void Process(const se::Shader* shader) = 0;
	protected:

	private:
	};

}

