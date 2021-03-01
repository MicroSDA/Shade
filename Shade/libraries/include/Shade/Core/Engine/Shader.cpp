#include "stdafx.h"
#include "Shader.h"

se::Shader::Shader():
    m_Program(NULL)
{
	m_ShaderLayout = [](const void*, const se::Shader*) { SE_DEBUG_PRINT("Shader layout isn't set!", se::SLCode::Warning); };
}

se::Shader* se::Shader::CreateFromFile(const std::string& filePath)
{
	std::ifstream _File;
	_File.open(filePath, std::ifstream::in);
	if (_File.is_open())
	{
		se::Shader* pShader = new se::Shader;

		std::string line;
		while (_File.good())
		{
			std::getline(_File, line);
			if (line == "#vertex")
				pShader->m_Shaders.push_back(pShader->CreateShader(pShader->LoadShader(_File), GL_VERTEX_SHADER));

			if (line == "#fragment")
				pShader->m_Shaders.push_back(pShader->CreateShader(pShader->LoadShader(_File), GL_FRAGMENT_SHADER));

			if (line == "#geometry")
				pShader->m_Shaders.push_back(pShader->CreateShader(pShader->LoadShader(_File), GL_GEOMETRY_SHADER));

			if (line == "#---")
				break;
		}

		_File.close();
		if (pShader->m_Shaders.size() == 0)
		{
			delete pShader;
			SE_DEBUG_PRINT("Shader count 0 in '" + filePath + "'", se::SLCode::Warning);
			return nullptr;
		}

		pShader->m_Program = glCreateProgram();
		for (unsigned int i = 0; i < pShader->m_Shaders.size(); i++) {
			glAttachShader(pShader->m_Program, pShader->m_Shaders[i]);
		}
		glLinkProgram(pShader->m_Program);
		pShader->CheckShaderError(pShader->m_Program, GL_LINK_STATUS, true, "Error: Shader program linkin faild: ");
		glValidateProgram(pShader->m_Program);
		pShader->CheckShaderError(pShader->m_Program, GL_VALIDATE_STATUS, true, "Error: Shader program validate faild: ");

		return pShader;
	}
	else
	{
		SE_DEBUG_PRINT("Failed to opne shader file '" + filePath + "'", se::SLCode::Warning);
		return nullptr;
	}

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

		SE_DEBUG_PRINT(errorMessage + ": '" + error + "'", se::SLCode::Error);
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

inline GLint se::Shader::GetAttribLocation(const std::string& name) const
{
	if (m_UniformLocation.find(name) != m_UniformLocation.end())
	{
		return m_UniformLocation[name];
	}
	else
	{
		GLint _Location = glGetAttribLocation(m_Program, name.c_str());
		m_UniformLocation[name] = _Location;
		return _Location;
	}
	
}

void se::Shader::SetLayout(void(*layout)(const void*, const se::Shader*))
{
	m_ShaderLayout = layout;
}

void se::Shader::Process(const void* entity)
{
	m_ShaderLayout(entity, this);
}

void se::Shader::SendCamera(const se::Camera* camera)
{
	SendUniform3Float("CameraPosition",                   camera->GetPosition());
	SendUniformMatrix4Float("ViewMatrix", GL_FALSE,       camera->GetView());
	SendUniformMatrix4Float("ProjectionMatrix", GL_FALSE, camera->GetProjection());
}