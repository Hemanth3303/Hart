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
			const std::uint32_t MAX_QUADS = 10000;
			const std::uint32_t MAX_VERTICES = MAX_QUADS * 4;
			const std::uint32_t MAX_INDICES = MAX_QUADS * 6;

			std::shared_ptr<Shader> shader;
			Maths::Mat4 viewProjectionMatrix;

			std::shared_ptr<VertexArray> quadVertexArray;
			std::shared_ptr<VertexBuffer> quadVertexBuffer;

			QuadVertex* quadVertexBufferBase = nullptr;
			QuadVertex* quadVertexBufferPtr = nullptr;

			std::uint32_t quadIndexCount = 0;
		};

		Renderer2DData renderer2dData;

		std::uint32_t Renderer2D::s_NumberOfDrawCalls = 0;

		void Renderer2D::Init() {
			HART_ENGINE_LOG("Initializing Renderer2D");
			std::vector<std::uint32_t> quadIndices;
			quadIndices.resize(renderer2dData.MAX_INDICES);

			std::uint32_t offset = 0;
			for (std::size_t i = 0; i < renderer2dData.MAX_INDICES; i += 6) {
				quadIndices.at(i + 0) = offset + 0;
				quadIndices.at(i + 1) = offset + 1;
				quadIndices.at(i + 2) = offset + 3;

				quadIndices.at(i + 3) = offset + 1;
				quadIndices.at(i + 4) = offset + 2;
				quadIndices.at(i + 5) = offset + 3;

				offset += 4;
			}

			BufferLayout layout = {
				{ ShaderDataType::Float3, "aPosition" },
				{ ShaderDataType::Float4, "aColor" },
				{ ShaderDataType::Float2, "aTexCoord" }
			};
			renderer2dData.quadVertexArray = std::make_shared<VertexArray>();
			renderer2dData.quadVertexArray->bind();

			renderer2dData.quadVertexBuffer = std::make_shared<VertexBuffer>(renderer2dData.MAX_VERTICES * static_cast < std::uint32_t>(sizeof(QuadVertex)));
			renderer2dData.quadVertexBuffer->setLayout(layout);
			renderer2dData.quadVertexArray->addVertexBuffer(renderer2dData.quadVertexBuffer);

			renderer2dData.quadVertexBufferBase = new QuadVertex[renderer2dData.MAX_VERTICES];

			std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(quadIndices.data(), renderer2dData.MAX_INDICES);
			renderer2dData.quadVertexArray->setIndexBuffer(indexBuffer); // this unbinds quadVertexArray
		}

		void Renderer2D::DeInit() {
			HART_ENGINE_LOG("DeInitializing Renderer2D");

			delete renderer2dData.quadVertexBufferBase;

			renderer2dData.quadVertexArray->getIndexBuffer()->unbind();
			renderer2dData.quadVertexArray->unbind();
			renderer2dData.shader->unbind();
		}

		void Renderer2D::BeginScene(OrthographicCamera& camera) {
			renderer2dData.shader = Application::s_Instance->getShader("DefaultShader2D");
			renderer2dData.viewProjectionMatrix = camera.getViewProjectionMatrix();

			HART_ASSERT_NOT_EQUAL(renderer2dData.shader, nullptr);
			HART_ASSERT_NOT_EQUAL(renderer2dData.quadVertexArray, nullptr);

			BeginBatch();

			renderer2dData.shader->bind();
			renderer2dData.shader->setUniform("uViewProjectionMatrix", renderer2dData.viewProjectionMatrix);

			renderer2dData.quadVertexArray->bind();
			renderer2dData.quadVertexArray->getIndexBuffer()->bind();
		}

		void Renderer2D::EndScene() {
			Flush();
			s_NumberOfDrawCalls = 0;
		}

		void Renderer2D::setCustomShader(const std::shared_ptr<Shader>& shader) {
			renderer2dData.shader = shader;
			shader->bind();
		}

		void Renderer2D::unsetCustomShader() {
			renderer2dData.shader = Application::s_Instance->getShader("DefaultShader2D");
			renderer2dData.shader->bind();
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color) {
			DrawQuad(Maths::Vec3(position, 1.0f), size, color);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color) {
			Maths::Vec4 quadColor = Maths::Vec4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f);

			if (renderer2dData.quadIndexCount >= renderer2dData.MAX_INDICES) {
				Flush();
				BeginBatch();
			}

			renderer2dData.quadVertexBufferPtr->position = { position.x + size.x, position.y + size.y, position.z };
			renderer2dData.quadVertexBufferPtr->color = quadColor;
			renderer2dData.quadVertexBufferPtr->textureCoords = { 1.0f, 1.0f };
			renderer2dData.quadVertexBufferPtr++;

			renderer2dData.quadVertexBufferPtr->position = { position.x + size.x, position.y, position.z };
			renderer2dData.quadVertexBufferPtr->color = quadColor;
			renderer2dData.quadVertexBufferPtr->textureCoords = { 1.0f, 0.0f };
			renderer2dData.quadVertexBufferPtr++;

			renderer2dData.quadVertexBufferPtr->position = position;
			renderer2dData.quadVertexBufferPtr->color = quadColor;
			renderer2dData.quadVertexBufferPtr->textureCoords = { 0.0f, 0.0f };
			renderer2dData.quadVertexBufferPtr++;

			renderer2dData.quadVertexBufferPtr->position = { position.x, position.y + size.y, position.z };
			renderer2dData.quadVertexBufferPtr->color = quadColor;
			renderer2dData.quadVertexBufferPtr->textureCoords = { 0.0f, 1.0f };
			renderer2dData.quadVertexBufferPtr++;

			renderer2dData.quadIndexCount += 6;
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

			renderer2dData.shader->setUniform("uColor", quadColor);
			renderer2dData.shader->setUniform("uModelMatrix", transformationMatrix);
			renderer2dData.shader->setUniform("uTexture", tex.getSlot());
			renderer2dData.shader->setUniform("uTextureTilingFactor", 1.0f);
			RenderCommand::DrawIndexed(renderer2dData.quadVertexArray);
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint, float textureTilingFactor) {
			DrawQuad(Maths::Vec3(position, 1.0f), size, 0.0f, texture, textureTint, textureTilingFactor);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint, float textureTilingFactor) {
			Maths::Mat4 transformationMatrix = Maths::Mat4::translate(position) * Maths::Mat4::scale(size);
			Maths::Vec4 quadColor = Maths::Vec4(textureTint.x / 255.0f, textureTint.y / 255.0f, textureTint.z / 255.0f, textureTint.w / 255.0f);

			texture->bind();
			renderer2dData.shader->setUniform("uColor", quadColor);
			renderer2dData.shader->setUniform("uModelMatrix", transformationMatrix);
			renderer2dData.shader->setUniform("uTexture", texture->getSlot());
			renderer2dData.shader->setUniform("uTextureTilingFactor", textureTilingFactor);
			RenderCommand::DrawIndexed(renderer2dData.quadVertexArray);
		}

		void Renderer2D::DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint, float textureTilingFactor) {
			DrawQuad(Maths::Vec3(position, 1.0f), size, angleD, texture, textureTint, textureTilingFactor);
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint, float textureTilingFactor) {
			Maths::Mat4 transformationMatrix = Maths::Mat4::translate(position) * Maths::Mat4::rotate(angleD, Maths::Vec3(0.0f, 0.0f, 1.0f)) * Maths::Mat4::scale(size);
			Maths::Vec4 quadColor = Maths::Vec4(textureTint.x / 255.0f, textureTint.y / 255.0f, textureTint.z / 255.0f, textureTint.w / 255.0f);

			texture->bind();
			renderer2dData.shader->setUniform("uColor", quadColor);
			renderer2dData.shader->setUniform("uModelMatrix", transformationMatrix);
			renderer2dData.shader->setUniform("uTexture", texture->getSlot());
			renderer2dData.shader->setUniform("uTextureTilingFactor", textureTilingFactor);
			RenderCommand::DrawIndexed(renderer2dData.quadVertexArray);
		}

		void Renderer2D::BeginBatch() {
			renderer2dData.quadVertexBufferPtr = renderer2dData.quadVertexBufferBase;
			renderer2dData.quadIndexCount = 0;
		}

		void Renderer2D::Flush() {
			std::uint32_t dataSize = static_cast<std::uint32_t>(reinterpret_cast<std::uint8_t*>(renderer2dData.quadVertexBufferPtr) - reinterpret_cast<std::uint8_t*>(renderer2dData.quadVertexBufferBase));
			renderer2dData.quadVertexBuffer->setData(renderer2dData.quadVertexBufferBase, dataSize);

			RenderCommand::DrawIndexed(renderer2dData.quadVertexArray, renderer2dData.quadIndexCount);
			s_NumberOfDrawCalls++;
		}
	}
}