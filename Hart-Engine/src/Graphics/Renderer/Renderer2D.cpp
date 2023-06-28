#include "HartPch.hpp"
#include "Renderer2D.hpp"
#include "Core/HartApplication.hpp"

namespace Hart {
	namespace Graphics {
		std::unique_ptr<Scene2DData> Renderer2D::s_SceneData = std::make_unique<Scene2DData>();

		void Renderer2D::Init() {
			HART_ENGINE_LOG("Initializing Renderer2D");
			std::array<float, 20> vertices = {
				//position          //texture coords
				1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
				1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
			   -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
			   -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
			};
			std::array<std::uint32_t, 6> indices = {
				0, 1, 3,
				1, 2, 3,
			};

			BufferLayout layout = {
				{ ShaderDataType::Float3, "aPosition" },
				{ ShaderDataType::Float2, "aTexCoord" }
			};
			s_SceneData->vertexArray = std::make_shared<VertexArray>();
			s_SceneData->vertexArray->bind();

			std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(vertices.data(), static_cast<std::uint32_t>(sizeof(vertices)));
			vertexBuffer->setLayout(layout);
			s_SceneData->vertexArray->addVertexBuffer(vertexBuffer);

			std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices.data(), static_cast<std::uint32_t>(indices.size()));
			s_SceneData->vertexArray->setIndexBuffer(indexBuffer); // this unbinds vertexArray
		}

		void Renderer2D::DeInit() {
			HART_ENGINE_LOG("DeInitializing Renderer2D");
			s_SceneData->vertexArray->getIndexBuffer()->unbind();
			s_SceneData->vertexArray->unbind();
			s_SceneData->shader->unbind();
		}

		void Renderer2D::BeginScene(OrthographicCamera& camera) {
			s_SceneData->shader = Application::s_Instance->getShader("DefaultShader2D");
			s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();

			BeginSceneImplementation();
		}

		void Renderer2D::BeginScene(OrthographicCamera& camera, const std::shared_ptr<Shader>& sceneShader) {
			s_SceneData->shader = sceneShader;
			s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();

			BeginSceneImplementation();
		}

		void Renderer2D::EndScene() {
			// TODO
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color) {
			DrawQuad(position, size, 0.0f, color);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color) {
			DrawQuad(position, size, 0.0f, color);
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& color) {
			DrawQuad(Maths::Vec3(position, 1.0f), size, angleD, color);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& color) {
			Maths::Mat4 transformationMatrix = Maths::Mat4::translate(position) * Maths::Mat4::rotate(angleD, Maths::Vec3(0.0f, 0.0f, 1.0f)) * Maths::Mat4::scale(size);
			Maths::Vec4 quadColor = Maths::Vec4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f);

			std::uint32_t whiteTextureData = 0xffffffff;
			Texture2D tex(&whiteTextureData, 1, 1);
			tex.bind();

			s_SceneData->shader->setUniform("uColor", quadColor);
			s_SceneData->shader->setUniform("uModelMatrix", transformationMatrix);
			s_SceneData->shader->setUniform("uTexture", tex.getSlot());
			RenderCommand::DrawIndexed(s_SceneData->vertexArray);
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint) {
			DrawQuad(position, size, 0.0f, texture, textureTint);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint) {
			DrawQuad(position, size, 0.0f, texture, textureTint);
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint) {
			DrawQuad(Maths::Vec3(position, 1.0f), size, angleD, texture, textureTint);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint) {
			Maths::Mat4 transformationMatrix = Maths::Mat4::translate(position) * Maths::Mat4::rotate(angleD, Maths::Vec3(0.0f, 0.0f, 1.0f)) * Maths::Mat4::scale(size);
			Maths::Vec4 quadColor = Maths::Vec4(textureTint.x / 255.0f, textureTint.y / 255.0f, textureTint.z / 255.0f, textureTint.w / 255.0f);

			texture->bind();
			s_SceneData->shader->setUniform("uColor", quadColor);
			s_SceneData->shader->setUniform("uModelMatrix", transformationMatrix);
			s_SceneData->shader->setUniform("uTexture", texture->getSlot());
			RenderCommand::DrawIndexed(s_SceneData->vertexArray);

		}
		void Renderer2D::BeginSceneImplementation() {
			HART_ASSERT_NOT_EQUAL(s_SceneData->shader, nullptr);
			HART_ASSERT_NOT_EQUAL(s_SceneData->vertexArray, nullptr);
			s_SceneData->shader->bind();
			s_SceneData->shader->setUniform("uViewProjectionMatrix", s_SceneData->viewProjectionMatrix);

			s_SceneData->vertexArray->bind();
			s_SceneData->vertexArray->getIndexBuffer()->bind();
		}
	}
}