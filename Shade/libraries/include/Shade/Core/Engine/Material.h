#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glm/glm.hpp"
#include "Shade/Core/Engine/Shader.h"
namespace se
{
	class  SE_API Material
	{
	public:
		Material();
		virtual ~Material();

		void SetName(const std::string& name);

		void SetAmbientColor(const float& r, const float& g, const float& b);
		void SetAmbientColor(const glm::vec3& color);

		void SetDiffuseColor(const float& r, const float& g, const float& b);
		void SetDiffuseColor(const glm::vec3& color);

		void SetSpecularColor(const float& r, const float& g, const float& b);
		void SetSpecularColor(const glm::vec3& color);

		void SetTransparentMask(const float& r, const float& g, const float& b);
		void SetTransparentMask(const glm::vec3& color);

		void SetShinines(const float& value);
		void SetShininesStrength(const float& value);

		const std::string& GetName() const;
		const glm::vec3& GetAmbientColor() const;
		const glm::vec3& GetDiffuseColor() const;
		const glm::vec3& GetSpecularColor() const;
		const glm::vec3& GetTransparentMask() const;
		const float& GetShinines() const;
		const float& GetShininesStrength() const;

		void Process(const se::Shader* shader) const;
	private:
		std::string m_Name;
		glm::vec3   m_AmbientColor;
		glm::vec3   m_DiffuseColor;
		glm::vec3   m_SpecularColor;
		glm::vec3   m_TransparentMask;
		float       m_ShininesStrength;
		float       m_Shinines;
	};
}

