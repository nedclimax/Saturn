#pragma once
#include "Saturn/Renderer/Shader.h"

namespace Saturn
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string vertexSrc, const std::string fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformVec2f(const std::string& name, const glm::vec2& vector);
		void UploadUniformVec3f(const std::string& name, const glm::vec3& vector);
		void UploadUniformVec4f(const std::string& name, const glm::vec4& vector);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};
}
