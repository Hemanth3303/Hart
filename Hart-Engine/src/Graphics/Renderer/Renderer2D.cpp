#include "HartPch.hpp"
#include "Renderer2D.hpp"
#include "../Primitives/VertexBuffer.hpp"
#include "../Primitives/IndexBuffer.hpp"
#include "../Primitives/VertexArray.hpp"
#include "../Primitives/Shader.hpp"
#include "Core/HartApplication.hpp"

namespace Hart {
	namespace Graphics {
		struct QuadVertex {
		public:
			Maths::Vec3 position;
			Maths::Vec4 color;
			Maths::Vec2 textureCoords;
		};

		struct Renderer2DData {
		public:
			std::shared_ptr<Shader> shader;
			Maths::Mat4 viewProjectionMatrix;

			std::shared_ptr<VertexArray> quadVertexArray;
			std::shared_ptr<VertexBuffer> quadVertexBuffer;

			// TODO: Add vertex types
		};

		Renderer2DData s_Data;

		void Renderer2D::Init() {
			HART_ENGINE_LOG("Initializing Renderer2D");
			// -0.5 to +0.5 gives a unit square quad in normalized device coordinates(ndc)
			std::array<float, 20> quadVertices = {
				//position          //texture coords
				0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
				0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			   -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
			};
			std::array<std::uint32_t, 6> quadIndices = {
				0, 1, 3,
				1, 2, 3,
			};

			BufferLayout layout = {
				{ ShaderDataType::Float3, "aPosition" },
				{ ShaderDataType::Float2, "aTexCoord" }
			};
			s_Data.quadVertexArray = std::make_shared<VertexArray>();
			s_Data.quadVertexArray->bind();

			s_Data.quadVertexBuffer = std::make_shared<VertexBuffer>(quadVertices.data(), static_cast<std::uint32_t>(sizeof(quadVertices)));
			s_Data.quadVertexBuffer->setLayout(layout);
			s_Data.quadVertexArray->addVertexBuffer(s_Data.quadVertexBuffer);

			std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(quadIndices.data(), static_cast<std::uint32_t>(quadIndices.size()));
			s_Data.quadVertexArray->setIndexBuffer(indexBuffer); // this unbinds quadVertexArray
		}

		void Renderer2D::DeInit() {
			HART_ENGINE_LOG("DeInitializing Renderer2D");
			s_Data.quadVertexArray->getIndexBuffer()->unbind();
			s_Data.quadVertexArray->unbind();
			s_Data.shader->unbind();
		}

		void Renderer2D::BeginScene(OrthographicCamera& camera) {
			s_Data.shader = Application::s_Instance->getShader("DefaultShader2D");
			s_Data.viewProjectionMatrix = camera.getViewProjectionMatrix();

			BeginSceneImplementation();
		}

		void Renderer2D::BeginScene(OrthographicCamera& camera, const std::shared_ptr<Shader>& sceneShader) {
			s_Data.shader = sceneShader;
			s_Data.viewProjectionMatrix = camera.getViewProjectionMatrix();

			BeginSceneImplementation();
		}

		void Renderer2D::EndScene() {
			// TODO
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color) {
			DrawQuad(Maths::Vec3(position, 1.0f), size, color);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color) {
			Maths::Mat4 transformationMatrix = Maths::Mat4::translate(position) * Maths::Mat4::scale(size);
			Maths::Vec4 quadColor = Maths::Vec4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f);

			std::uint32_t whiteTextureData = 0xffffffff;
			Texture2D tex(&whiteTextureData, 1, 1);
			tex.bind();

			s_Data.shader->setUniform("uColor", quadColor);
			s_Data.shader->setUniform("uModelMatrix", transformationMatrix);
			s_Data.shader->setUniform("uTexture", tex.getSlot());
			s_Data.shader->setUniform("uTextureTilingFactor", 1.0f);
			RenderCommand::DrawIndexed(s_Data.quadVertexArray);
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

			s_Data.shader->setUniform("uColor", quadColor);
			s_Data.shader->setUniform("uModelMatrix", transformationMatrix);
			s_Data.shader->setUniform("uTexture", tex.getSlot());
			s_Data.shader->setUniform("uTextureTilingFactor", 1.0f);
			RenderCommand::DrawIndexed(s_Data.quadVertexArray);
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint, float textureTilingFactor) {
			DrawQuad(Maths::Vec3(position, 1.0f), size, 0.0f, texture, textureTint, textureTilingFactor);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint, float textureTilingFactor) {
			Maths::Mat4 transformationMatrix = Maths::Mat4::translate(position) * Maths::Mat4::scale(size);
			Maths::Vec4 quadColor = Maths::Vec4(textureTint.x / 255.0f, textureTint.y / 255.0f, textureTint.z / 255.0f, textureTint.w / 255.0f);

			texture->bind();
			s_Data.shader->setUniform("uColor", quadColor);
			s_Data.shader->setUniform("uModelMatrix", transformationMatrix);
			s_Data.shader->setUniform("uTexture", texture->getSlot());
			s_Data.shader->setUniform("uTextureTilingFactor", textureTilingFactor);
			RenderCommand::DrawIndexed(s_Data.quadVertexArray);
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint, float textureTilingFactor) {
			DrawQuad(Maths::Vec3(position, 1.0f), size, angleD, texture, textureTint, textureTilingFactor);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint, float textureTilingFactor) {
			Maths::Mat4 transformationMatrix = Maths::Mat4::translate(position) * Maths::Mat4::rotate(angleD, Maths::Vec3(0.0f, 0.0f, 1.0f)) * Maths::Mat4::scale(size);
			Maths::Vec4 quadColor = Maths::Vec4(textureTint.x / 255.0f, textureTint.y / 255.0f, textureTint.z / 255.0f, textureTint.w / 255.0f);

			texture->bind();
			s_Data.shader->setUniform("uColor", quadColor);
			s_Data.shader->setUniform("uModelMatrix", transformationMatrix);
			s_Data.shader->setUniform("uTexture", texture->getSlot());
			s_Data.shader->setUniform("uTextureTilingFactor", textureTilingFactor);
			RenderCommand::DrawIndexed(s_Data.quadVertexArray);
		}

		void Renderer2D::BeginSceneImplementation() {
			HART_ASSERT_NOT_EQUAL(s_Data.shader, nullptr);
			HART_ASSERT_NOT_EQUAL(s_Data.quadVertexArray, nullptr);
			s_Data.shader->bind();
			s_Data.shader->setUniform("uViewProjectionMatrix", s_Data.viewProjectionMatrix);

			s_Data.quadVertexArray->bind();
			s_Data.quadVertexArray->getIndexBuffer()->bind();
		}
	}
}