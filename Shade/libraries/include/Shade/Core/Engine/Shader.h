#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Asset.h"
#include "Shade/Core/Util/Log.h"
#include "Vendors/glad/glad.h"

namespace se
{
	class SE_API Shader : public se::Asset
	{
	public:
		Shader(const AssetData* data);
		virtual ~Shader();

		inline void Bind() const;
		inline static void UnBind();
		const GLuint& GetProgram() const { return m_Program; }
		inline void SendUniformMatrix4fv(const GLint& location, const GLboolean& isTransopnse, const GLfloat* value) const
		{
			glUniformMatrix4fv(location, 1, isTransopnse, value);
		}

		virtual void Load() override;
		virtual void Init() override;
	protected:
		std::vector<GLuint> m_Shaders;
		GLuint              m_Program;
	private:
		GLuint CreateShader(const std::string& text, GLenum shaderType);
		std::string LoadShader(std::ifstream& file);
		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	};

}

