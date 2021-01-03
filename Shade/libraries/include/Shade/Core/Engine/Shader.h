#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Asset.h"
#include "Shade/Core/Util/Log.h"
#include "Vendors/glad/glad.h"
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtc/type_ptr.hpp"
namespace se
{
	class SE_API Shader : public se::Asset
	{
	public:
		Shader(const std::string& parrentClassName, const se::AssetData* data);
		virtual ~Shader();

		inline void Bind() const;
		inline static void UnBind();
		const GLuint& GetProgram() const { return m_Program; }

		inline void SendUniformMatrix3Float(const std::string& name, const GLboolean& isTransopnse, const glm::fmat3& value) const;
		inline void SendUniformMatrix4Float(const std::string& name, const GLboolean& isTransopnse, const glm::fmat4& value) const;
		inline void SendUniform1Int(const std::string& name, const GLint& value) const;
		inline void SendUniform2Int(const std::string& name, const glm::ivec2& value) const;
		inline void SendUniform3Int(const std::string& name, const glm::ivec3& value) const;
		inline void SendUniform4Int(const std::string& name, const glm::ivec4& value) const;
		inline void SendUniform1Float(const std::string& name, const GLfloat& value) const;
		inline void SendUniform2Float(const std::string& name, const glm::fvec2& value) const;
		inline void SendUniform3Float(const std::string& name, const glm::fvec3& value) const;
		inline void SendUniform4Float(const std::string& name, const glm::fvec4& value) const;
		inline void SendUniformBool(const std::string& name, const bool& value) const;

		virtual void Load() override;
		virtual void Init() override;
	protected:
		std::vector<GLuint> m_Shaders;
		GLuint              m_Program;

		mutable std::unordered_map<std::string, GLint> m_UniformLocation;
	private:
		GLuint CreateShader(const std::string& text, GLenum shaderType);
		std::string LoadShader(std::ifstream& file);
		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

		inline GLint GetUniformLocation(const std::string& name) const;
	};

}

