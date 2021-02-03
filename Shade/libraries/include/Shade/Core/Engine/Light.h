#pragma once
#include "Shade/Core/Engine/Environment.h"
#include "Vendors/glm/glm.hpp"

namespace se
{
	class SE_API Light : public se::Environment
	{
	public:
		Light();
		virtual ~Light();
		inline void SetAmbientColor(const  float& r, const float& g, const float& b) { m_AmbientColor = glm::vec3(r, g, b); }
		inline void SetDiffuseColor(const  float& r, const float& g, const float& b) { m_DiffuseColor = glm::vec3(r, g, b); }
		inline void SetSpecularColor(const float& r, const float& g, const float& b) { m_SpecularColor = glm::vec3(r, g, b); }
		inline void SetAmbientColor(const   glm::vec3& color) { m_AmbientColor = color; }
		inline void SetDiffuseColor(const   glm::vec3& color) { m_DiffuseColor = color; }
		inline void SetSpecularColor(const  glm::vec3& color) { m_SpecularColor = color; }
		inline const glm::vec3& GetAmbientColor() const { return m_AmbientColor; }
		inline const glm::vec3& GetDiffuseColor() const { return m_DiffuseColor; }
		inline const glm::vec3& GetSpecularColor() const { return m_SpecularColor; }

		inline glm::vec3& GetAmbientColorRef() { return m_AmbientColor; }
		inline glm::vec3& GetDiffuseColorRef() { return m_DiffuseColor; }
		inline glm::vec3& GetSpecularColorRef() { return m_SpecularColor; }

		virtual void OnUpdate(const se::Timer& deltaTime) = 0;
		virtual void Process(const se::Shader* shader) = 0;
	protected:
		glm::vec3  m_AmbientColor;
		glm::vec3  m_DiffuseColor;
		glm::vec3  m_SpecularColor;
	private:
	};

}

