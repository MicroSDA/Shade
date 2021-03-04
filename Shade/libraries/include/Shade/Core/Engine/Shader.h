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
		inline GLint SendUniformMatrix3Float(const std::string& name, const GLboolean& isTransopnse, const glm::fmat3& value) const
		{
			GLint location = GetUniformLocation(name);
			if(location)
				glUniformMatrix3fv(location, 1, isTransopnse, glm::value_ptr(value));
			return location;
		}
		inline GLint SendUniformMatrix4Float(const std::string& name, const GLboolean& isTransopnse, const glm::fmat4& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniformMatrix4fv(location, 1, isTransopnse, glm::value_ptr(value));
			return location;
		}
		inline GLint SendUniform1Int(const std::string& name, const GLint& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniform1i(location, value);
			return location;
		}
		inline GLint SendUniform2Int(const std::string& name, const glm::ivec2& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniform2i(location, value.x, value.y);
			return location;
		}
		inline GLint SendUniform3Int(const std::string& name, const glm::ivec3& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniform3i(location, value.x, value.y, value.z);
			return location;
		}
		inline GLint SendUniform4Int(const std::string& name, const glm::ivec4& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniform4i(location, value.x, value.y, value.z, value.a);
			return location;
		}
		inline GLint SendUniform1Float(const std::string& name, const GLfloat& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniform1f(location, value);
			return location;
		}
		inline GLint SendUniform2Float(const std::string& name, const glm::fvec2& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniform2f(location, value.x, value.y);
			return location;
		}
		inline GLint SendUniform3Float(const std::string& name, const glm::fvec3& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniform3f(location, value.x, value.y, value.z);
			return location;
		}
		inline GLint SendUniform4Float(const std::string& name, const glm::fvec4& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniform4f(location, value.x, value.y, value.z, value.a);
			return location;
		}
		inline GLint SendUniformBool(const std::string& name, const bool& value) const
		{
			GLint location = GetUniformLocation(name);
			if (location)
				glUniform1i(location, value);
			return location;
		}
		inline GLint SetAttribLocation(const std::string& name) const
		{
			GLint location = GetAttribLocation(name);
			if (location)
				glBindAttribLocation(m_Program, location, name.c_str());
			return location;
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

