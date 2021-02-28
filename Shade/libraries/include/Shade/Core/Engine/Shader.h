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
	class SE_API Shader : public se::Asset
	{
	public:
		Shader();
		virtual ~Shader();
		inline void Bind() const;
		inline static void UnBind();
		const GLuint& GetProgram() const { return m_Program; }
		// TODO: implement inline or remove
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
		inline void SetAttribLocation(const std::string& name) const;
		virtual void LoadFromAssetData(const std::string& assetId, se::AssetData& data) override;
		virtual void Init() override;
		void SetLayout(void(*layout)(const void*, const se::Shader*));
		void Process(const void* entity);

		void SendCamera(const se::Camera* camera);
	protected:
		std::vector<GLuint> m_Shaders;
		GLuint              m_Program;
		mutable std::unordered_map<std::string, GLint> m_UniformLocation;
	private:
		void (*m_ShaderLayout)(const void*, const se::Shader*) = nullptr;

		GLuint CreateShader(const std::string& text, GLenum shaderType);
		std::string LoadShader(std::ifstream& file);
		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

		inline GLint GetUniformLocation(const std::string& name) const;
		inline GLint GetAttribLocation(const std::string& name) const;
	};

}

