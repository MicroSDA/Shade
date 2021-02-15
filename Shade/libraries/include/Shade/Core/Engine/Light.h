#pragma once
#include "Shade/Core/Engine/Environment.h"
#include "Vendors/glm/glm.hpp"

namespace se
{
	class SE_API Light : public se::Environment
	{
	public:
		Light(const se::Environment::Type& type);
		virtual ~Light();
		void SetAmbientColor(const  float& r, const float& g, const float& b);
		void SetDiffuseColor(const  float& r, const float& g, const float& b);
		void SetSpecularColor(const float& r, const float& g, const float& b);
		void SetAmbientColor(const   glm::vec3& color);
		void SetDiffuseColor(const   glm::vec3& color);
		void SetSpecularColor(const  glm::vec3& color);
		const glm::vec3& GetAmbientColor() const;
		const glm::vec3& GetDiffuseColor() const;
		const glm::vec3& GetSpecularColor() const;

		glm::vec3& GetAmbientColor();
		glm::vec3& GetDiffuseColor();
		glm::vec3& GetSpecularColor();

		virtual void OnUpdate(const se::Timer& deltaTime) = 0;
		virtual void Process(const se::Shader* shader) = 0;
	protected:
		glm::vec3  m_AmbientColor;
		glm::vec3  m_DiffuseColor;
		glm::vec3  m_SpecularColor;
	private:
	};

}

