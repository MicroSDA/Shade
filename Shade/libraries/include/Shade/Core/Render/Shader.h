#pragma once
#include <Shade/Utilities/Log.h>
#include <Shade/Core/asset/Asset.h>
#include <Shade/Vendors/glad/glad.h>

#include <string>
#include <vector>
#include <functional>

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
		const GLuint& GetProgram() const { return m_Program; }// TODO should be like reference

		inline void SendUniformMatrix4fv(const GLint& location, const GLboolean& isTransopnse, const GLfloat* value) const 
		{
			glUniformMatrix4fv(location, 1, isTransopnse, value);
		}
		//virtual void Update() = 0; // Take function lambda 
		// Inherited via Asset
		virtual void Load() override;
	protected:
		std::vector<GLuint> m_Shaders;
		GLuint              m_Program;
	private:
		GLuint CreateShader(const std::string& text, GLenum shaderType);
		std::string LoadShader(std::ifstream& file);
		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

		
	};
}


