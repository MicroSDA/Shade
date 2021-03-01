#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Asset.h"
#include "Shade/Core/Util/Log.h"
#include "Vendors/glad/glad.h"
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtc/type_ptr.hpp"
#include "Shade/Core/Engine/Entity.h"
#include "Shade/Core/Engine/Camera.h"
namespace se
{
	class SE_API Shader
	{
	public:
		struct ShaderMeta
		{
			std::string Path;
			enum class SType : uint8_t
			{
				Vertex,
				Fragment,
				Geometry
			} Type;
		};


		static se::Shader* CreateFromFile(const std::string& filePath);
		virtual ~Shader();


		inline void Bind() const;
		inline static void UnBind();
		const GLuint& GetProgram() const { return m_Program; }
		inline void SendUniformMatrix3Float(const std::string& name, const GLboolean& isTransopnse, const glm::fmat3& value) const
		{
			glUniformMatrix3fv(GetUniformLocation(name), 1, isTransopnse, glm::value_ptr(value));
		}
		inline void SendUniformMatrix4Float(const std::string& name, const GLboolean& isTransopnse, const glm::fmat4& value) const
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, isTransopnse, glm::value_ptr(value));
		}
		inline void SendUniform1Int(const std::string& name, const GLint& value) const
		{
			glUniform1i(GetUniformLocation(name), value);
		}
		inline void SendUniform2Int(const std::string& name, const glm::ivec2& value) const
		{
			glUniform2i(GetUniformLocation(name), value.x, value.y);
		}
		inline void SendUniform3Int(const std::string& name, const glm::ivec3& value) const
		{
			glUniform3i(GetUniformLocation(name), value.x, value.y, value.z);
		}
		inline void SendUniform4Int(const std::string& name, const glm::ivec4& value) const
		{
			glUniform4i(GetUniformLocation(name), value.x, value.y, value.z, value.a);
		}
		inline void SendUniform1Float(const std::string& name, const GLfloat& value) const
		{
			glUniform1f(GetUniformLocation(name), value);
		}
		inline void SendUniform2Float(const std::string& name, const glm::fvec2& value) const
		{
			glUniform2f(GetUniformLocation(name), value.x, value.y);
		}
		inline void SendUniform3Float(const std::string& name, const glm::fvec3& value) const
		{
			glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
		}
		inline void SendUniform4Float(const std::string& name, const glm::fvec4& value) const
		{
			glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.a);
		}
		inline void SendUniformBool(const std::string& name, const bool& value) const
		{
			glUniform1i(GetUniformLocation(name), value);
		}
		inline void SetAttribLocation(const std::string& name) const
		{
			glBindAttribLocation(m_Program, GetAttribLocation(name), name.c_str());
		}
		void SetLayout(void(*layout)(const void*, const se::Shader*));
		void Process(const void* entity);
		void SendCamera(const se::Camera* camera);
	protected:
		std::vector<GLuint> m_Shaders;
		GLuint              m_Program;
		mutable std::unordered_map<std::string, GLint> m_UniformLocation;
	private:
		Shader();
		void (*m_ShaderLayout)(const void*, const se::Shader*) = nullptr;

		GLuint CreateShader(const std::string& text, GLenum shaderType);
		std::string LoadShader(std::ifstream& file);
		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

		inline GLint GetUniformLocation(const std::string& name) const;
		inline GLint GetAttribLocation(const std::string& name) const;
	};

}

