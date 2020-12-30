#include "stdafx.h"
#include "Shader.h"

se::Shader::Shader(const AssetData* data) :se::Asset(data),
    m_Program(NULL)
{
}

se::Shader::~Shader()
{
	// Delete program and shader
	glUseProgram(0);
	for (unsigned int i = 0; i < m_Shaders.size(); i++) {
		glDeleteShader(m_Shaders[i]);
	}
	glDeleteProgram(m_Program);
}

inline void se::Shader::Bind() const
{
	glUseProgram(m_Program);
}

inline void se::Shader::UnBind()
{
	glUseProgram(0);
}

void se::Shader::Load()
{
	std::ifstream _File;
	_File.open(m_AssetData->_Path, std::ifstream::in);
	if (_File.is_open())
	{
		_File.seekg(m_AssetData->_Offset);
		std::string line;
		while (_File.good())
		{
			std::getline(_File, line);
			if (line == "#vertex")
				m_Shaders.push_back(CreateShader(LoadShader(_File), GL_VERTEX_SHADER));

			if (line == "#fragment")
				m_Shaders.push_back(CreateShader(LoadShader(_File), GL_FRAGMENT_SHADER));
		
			if (line == "#geometry")
				//m_Shaders.push_back(CreateShader(LoadShader(_File), GL_GEOMETRY_SHADER));
		
			if (line == "#---")
				break;
		}

		_File.close();
		if (m_Shaders.size() == 0)
			throw se::ShadeException(std::string("Shaders count 0 in '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);

		m_Program = glCreateProgram();
		for (unsigned int i = 0; i < m_Shaders.size(); i++) {
			glAttachShader(m_Program, m_Shaders[i]);
		}
		glLinkProgram(m_Program);
		CheckShaderError(m_Program, GL_LINK_STATUS, true, "Error: Shader program linkin faild: ");
		glValidateProgram(m_Program);
		CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "Error: Shader program validate faild: ");
	}
	else
	{
		throw se::ShadeException(std::string("Failed to open shader file '" + m_AssetData->_Path + "' !").c_str(), se::SECode::Warning);
	}

}

GLuint se::Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		SE_DEBUG_PRINT("Error: Shader creation faild", se::SLCode::Error);
	}

	const GLchar* ShaderSourceSrtings[1];
	GLint ShaderSourceStringLengths[1];

	ShaderSourceSrtings[0] = text.c_str();
	ShaderSourceStringLengths[0] = text.length();


	glShaderSource(shader, 1, ShaderSourceSrtings, ShaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation faild: ");
	return shader;
}

std::string se::Shader::LoadShader(std::ifstream& file)
{
	std::string output;
	std::string line;
	if (file.is_open())
	{

		while (file.good())
		{
			std::getline(file, line);

			if (line == "#end")
			{
				break;
			}
			else
			{
				output.append(line + "\n");
			}
		}

	}
	else
	{
		SE_DEBUG_PRINT("Error: Shader creation faild", se::SLCode::Error);
	}

	return output;
}

void se::Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::string _Msg(errorMessage + ": '" + error + "'");
		SE_DEBUG_PRINT(_Msg.c_str(), se::SLCode::Error);
	}
}

inline GLint se::Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocation.find(name) != m_UniformLocation.end())
	{
		return m_UniformLocation[name];
	}
	else
	{
		GLint _Location = glGetUniformLocation(m_Program, name.c_str());
		m_UniformLocation[name] = _Location;
		return _Location;
	}
		
}

void se::Shader::Init()
{
}

inline void se::Shader::SendUniformMatrix3Float(const std::string& name, const GLboolean& isTransopnse, const glm::fmat3& value) const
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, isTransopnse, glm::value_ptr(value));
}

inline void se::Shader::SendUniformMatrix4Float(const std::string& name, const GLboolean& isTransopnse, const glm::fmat4& value) const
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, isTransopnse, glm::value_ptr(value));
}

inline void se::Shader::SendUniform1Int(const std::string& name, const GLint& value) const
{
	glUniform1i(GetUniformLocation(name), value);
}

inline void se::Shader::SendUniform2Int(const std::string& name, const glm::ivec2& value) const
{
	glUniform2i(GetUniformLocation(name), value.x, value.y);
}

inline void se::Shader::SendUniform3Int(const std::string& name, const glm::ivec3& value) const
{
	glUniform3i(GetUniformLocation(name), value.x, value.y, value.z);
}

inline void se::Shader::SendUniform4Int(const std::string& name, const glm::ivec4& value) const
{
	glUniform4i(GetUniformLocation(name), value.x, value.y, value.z, value.a);
}

inline void se::Shader::SendUniform1Float(const std::string& name, const GLfloat& value) const
{
	glUniform1f(GetUniformLocation(name), value);
}

inline void se::Shader::SendUniform2Float(const std::string& name, const glm::fvec2& value) const
{
	glUniform2f(GetUniformLocation(name), value.x, value.y);
}

inline void se::Shader::SendUniform3Float(const std::string& name, const glm::fvec3& value) const
{
	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

inline void se::Shader::SendUniform4Float(const std::string& name, const glm::fvec4& value) const
{
	glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.a);
}

inline void se::Shader::SendUniformBool(const std::string& name, const bool& value) const
{
	glUniform1i(GetUniformLocation(name), value);
}