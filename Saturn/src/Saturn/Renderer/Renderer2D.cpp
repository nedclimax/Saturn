#include "stpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"

#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Saturn
{
	struct Renderer2DData
	{
		Ref<VertexArray> QuadVA;
		Ref<Shader> Shader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DData();
		s_Data->QuadVA = VertexArray::Create();

		float quadVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> quadVB = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		quadVB->SetLayout({
			{ ShaderDataType::Vec3f, "a_Position" },
			{ ShaderDataType::Vec2f, "a_TexCoord" }
		});
		s_Data->QuadVA->AddVertexBuffer(quadVB);

		uint32_t quadIndices[] = { 0, 1, 2, 2, 3, 0 };

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		s_Data->QuadVA->SetIndexBuffer(quadIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->Shader = Shader::Create("assets/shaders/default2D.glsl");
		s_Data->Shader->Bind();
		s_Data->Shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::ShutDown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthoCamera& camera)
	{
		s_Data->Shader->Bind();
		s_Data->Shader->SetMat4f("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		s_Data->Shader->SetVec4f("u_Color", color);
		s_Data->WhiteTexture->Bind();

		glm::mat4 id = glm::mat4(1.0f);

		glm::mat4 transform = glm::translate(id, position) * glm::rotate(id, glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(id, { size.x, size.y, 1.0f });
		s_Data->Shader->SetMat4f("u_Transform", transform);
		
		s_Data->QuadVA->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVA);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation, const glm::vec4& tint)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, rotation, tint);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation, const glm::vec4& tint)
	{
		s_Data->Shader->SetVec4f("u_Color", tint);
		texture->Bind();

		glm::mat4 id = glm::mat4(1.0f);

		glm::mat4 transform = glm::translate(id, position) * glm::rotate(id, glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(id, { size.x, size.y, 1.0f });
		s_Data->Shader->SetMat4f("u_Transform", transform);


		s_Data->QuadVA->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVA);
	}
}