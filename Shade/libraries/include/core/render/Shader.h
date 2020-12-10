#pragma once
#include <utilities/Log.h>
#include <core/asset/Asset.h>
#include <glad/glad.h>
#include <string>
#include <vector>
namespace se
{
	enum SE_API ShaderType : unsigned int
	{
		Vertex   = 1,
		Fragment = 2,
		Geometry = 4
	};

	class SE_API Shader : public Asset
	{
	public:
		Shader(const AssetData* data);
		virtual ~Shader();
		inline void Bind() const;
		inline static void UnBind();
		//virtual void Update() = 0; // Take function lambda 
		// Inherited via Asset
		static const Asset* Load(const AssetData* data);
	protected:
		std::vector<GLuint> m_Shaders;
		GLuint              m_Program;
	private:
		GLuint CreateShader(const std::string& text, GLenum shaderType);
		std::string LoadShader(std::ifstream& file);
		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	};
}


