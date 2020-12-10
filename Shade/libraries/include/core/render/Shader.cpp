#include "Shader.h"
#include <iostream>

se::Shader::Shader(const AssetData* data)
{

	std::ifstream file;// Should be removed and created in manager as open file for multy thread loading
	
	file.open(data->_Path, std::ifstream::in);
	file.seekg(data->_Offset);

	if (!file.is_open())
	{
#ifdef SE_DEBUG
		DEBUG_PRINT("Error open shader file" + data->_Path, LogLevel::ERROR);
#else 
		DEBUG_SAVE("Error open shader file" + data->_Path, LogLevel::ERROR);
#endif // SE_DEBUG
		exit(-1);
	}

	std::string line;
	if (file.is_open())
	{

		while (file.good())
		{
			std::getline(file, line);
			if (line == "#vertex")
			{
				m_Shaders.push_back(CreateShader(LoadShader(file), GL_VERTEX_SHADER));
			}
			
			if (line == "#fragment")
			{
				m_Shaders.push_back(CreateShader(LoadShader(file), GL_FRAGMENT_SHADER));
			}

			if (line == "#geometry")
			{
				m_Shaders.push_back(CreateShader(LoadShader(file), GL_GEOMETRY_SHADER));
			}

			if (line == "#---")
			{
				break;
			}
		}

	}

	file.close();

	m_Program = glCreateProgram();
	for (unsigned int i = 0; i < m_Shaders.size(); i++) {
		glAttachShader(m_Program, m_Shaders[i]);
	}


	glLinkProgram(m_Program);
	CheckShaderError(m_Program, GL_LINK_STATUS, true, "Error: Shader program linkin faild: ");

	glValidateProgram(m_Program);
	CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "Error: Shader program validate faild: ");

}

se::Shader::~Shader()
{
}

inline void se::Shader::Bind() const
{
	glUseProgram(m_Program);
}

inline void se::Shader::UnBind()
{
	glUseProgram(0);
}

const se::Asset* se::Shader::Load(const AssetData* data)
{

	return new Shader(data);
}

GLuint se::Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0) 
	{
		DEBUG_PRINT("Error: Shader creation faild", LogLevel::ERROR);
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
			/*if (std::regex_search(line, match, include))
			{
				std::cout << match[1] << "\n";
			}*/
		}

	}
	else 
	{
		DEBUG_PRINT("Unable to laod shader: ", LogLevel::ERROR);
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

		DEBUG_PRINT(errorMessage + ": '" + error + "'", LogLevel::ERROR);
	}
}

/*const Asset* se::Shader::_Load(const AssetData* data)
{
	return nullptr;
}*/
