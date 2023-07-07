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
			float textureIndex = -1.0f; //invalid texture slot
		};

		struct Renderer2DData {
		public:
			const std::uint32_t MAX_QUADS = 10000;
			const std::uint32_t MAX_VERTICES = MAX_QUADS * 4;
			const std::uint32_t MAX_INDICES = MAX_QUADS * 6;
			static constexpr std::uint32_t MAX_TEXTURE_SLOTS_EXPECTED = 32;

			std::shared_ptr<Shader> shader;
			Maths::Mat4 viewProjectionMatrix;
			std::shared_ptr<Texture2D> whiteTexture;

			std::shared_ptr<VertexArray> quadVertexArray;
			std::shared_ptr<VertexBuffer> quadVertexBuffer;

			QuadVertex* quadVertexBufferBase = nullptr;
			QuadVertex* quadVertexBufferPtr = nullptr;

			std::uint32_t quadIndexCount = 0;
			
			std::array<std::shared_ptr<Texture2D>, MAX_TEXTURE_SLOTS_EXPECTED> textureSlots;
			std::uint32_t textureSlotIndex = 1; // slot_0 == white texture
		};

		Renderer2DData renderer2DData;

		std::uint32_t Renderer2D::s_NumberOfDrawCalls = 0;

		void Renderer2D::Init() {
			HART_ENGINE_LOG("Initializing Renderer2D");
			std::vector<std::uint32_t> quadIndices;
			quadIndices.resize(renderer2DData.MAX_INDICES);

			std::uint32_t offset = 0;
			for (std::size_t i = 0; i < renderer2DData.MAX_INDICES; i += 6) {
				quadIndices[i + 0] = offset + 0;
				quadIndices[i + 1] = offset + 1;
				quadIndices[i + 2] = offset + 3;

				quadIndices[i + 3] = offset + 1;
				quadIndices[i + 4] = offset + 2;
				quadIndices[i + 5] = offset + 3;

				offset += 4;
			}

			BufferLayout layout = {
				{ ShaderDataType::Float3, "aPosition" },
				{ ShaderDataType::Float4, "aColor" },
				{ ShaderDataType::Float2, "aTextureCoords" },
				{ ShaderDataType::Float, "aTextureIndex" },
			};

			renderer2DData.shader = Application::s_Instance->getShader("DefaultShader2D");

			renderer2DData.quadVertexArray = std::make_shared<VertexArray>();
			renderer2DData.quadVertexArray->bind();

			renderer2DData.quadVertexBuffer = std::make_shared<VertexBuffer>(renderer2DData.MAX_VERTICES * static_cast < std::uint32_t>(sizeof(QuadVertex)));
			renderer2DData.quadVertexBuffer->setLayout(layout);
			renderer2DData.quadVertexArray->addVertexBuffer(renderer2DData.quadVertexBuffer);

			renderer2DData.quadVertexBufferBase = new QuadVertex[renderer2DData.MAX_VERTICES];

			std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(quadIndices.data(), renderer2DData.MAX_INDICES);
			renderer2DData.quadVertexArray->setIndexBuffer(indexBuffer);

			std::uint32_t whiteTextureData = 0xffffffff;
			renderer2DData.whiteTexture = std::make_shared<Texture2D>(&whiteTextureData, 1, 1);
			renderer2DData.textureSlots[0] = renderer2DData.whiteTexture;

			std::int32_t samplers[renderer2DData.MAX_TEXTURE_SLOTS_EXPECTED];
			for (std::int32_t i = 0; i < renderer2DData.MAX_TEXTURE_SLOTS_EXPECTED; i++) {
				samplers[i] = i;
			}

			renderer2DData.shader->bind();
			renderer2DData.shader->setUniform("uTextures", samplers, renderer2DData.MAX_TEXTURE_SLOTS_EXPECTED);

		}

		void Renderer2D::DeInit() {
			HART_ENGINE_LOG("DeInitializing Renderer2D");

			delete renderer2DData.quadVertexBufferBase;

			renderer2DData.quadVertexArray->getIndexBuffer()->unbind();
			renderer2DData.quadVertexArray->unbind();
			renderer2DData.shader->unbind();
		}

		void Renderer2D::BeginScene(OrthographicCamera& camera) {
			renderer2DData.viewProjectionMatrix = camera.getViewProjectionMatrix();

			HART_ASSERT_NOT_EQUAL(renderer2DData.shader, nullptr);
			HART_ASSERT_NOT_EQUAL(renderer2DData.quadVertexArray, nullptr);

			renderer2DData.shader->bind();
			renderer2DData.shader->setUniform("uViewProjectionMatrix", renderer2DData.viewProjectionMatrix);

			renderer2DData.quadVertexArray->bind();
			renderer2DData.quadVertexArray->getIndexBuffer()->bind();

			BeginBatch();
		}

		void Renderer2D::EndScene() {
			Flush();
			s_NumberOfDrawCalls = 0;
		}

		void Renderer2D::setCustomShader(const std::shared_ptr<Shader>& shader) {
			renderer2DData.shader = shader;
			shader->bind();
		}

		void Renderer2D::unsetCustomShader() {
			renderer2DData.shader = Application::s_Instance->getShader("DefaultShader2D");
			renderer2DData.shader->bind();
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color) {
			if (renderer2DData.quadIndexCount >= renderer2DData.MAX_INDICES) {
				Flush();
				BeginBatch();
			}
			
			Maths::Vec4 quadColor = Maths::Vec4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f);
			float textureIndex = 0.0f;

			renderer2DData.quadVertexBufferPtr->position = { position.x + size.x, position.y + size.y, position.z };
			renderer2DData.quadVertexBufferPtr->color = quadColor;
			renderer2DData.quadVertexBufferPtr->textureCoords = { 1.0f, 1.0f };
			renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
			renderer2DData.quadVertexBufferPtr++;

			renderer2DData.quadVertexBufferPtr->position = { position.x + size.x, position.y, position.z };
			renderer2DData.quadVertexBufferPtr->color = quadColor;
			renderer2DData.quadVertexBufferPtr->textureCoords = { 1.0f, 0.0f };
			renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
			renderer2DData.quadVertexBufferPtr++;

			renderer2DData.quadVertexBufferPtr->position = position;
			renderer2DData.quadVertexBufferPtr->color = quadColor;
			renderer2DData.quadVertexBufferPtr->textureCoords = { 0.0f, 0.0f };
			renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
			renderer2DData.quadVertexBufferPtr++;

			renderer2DData.quadVertexBufferPtr->position = { position.x, position.y + size.y, position.z };
			renderer2DData.quadVertexBufferPtr->color = quadColor;
			renderer2DData.quadVertexBufferPtr->textureCoords = { 0.0f, 1.0f };
			renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
			renderer2DData.quadVertexBufferPtr++;

			renderer2DData.quadIndexCount += 6;
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& color) {
			
			Maths::Vec4 quadColor = Maths::Vec4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f);

		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint) {
			if ((renderer2DData.textureSlotIndex >= 31) || (renderer2DData.quadIndexCount >= renderer2DData.MAX_INDICES)) {
				Flush();
				BeginBatch();
			}

			Maths::Vec4 quadColor = Maths::Vec4(textureTint.x / 255.0f, textureTint.y / 255.0f, textureTint.z / 255.0f, textureTint.w / 255.0f);
			float textureIndex = 0.0f;

			for (std::size_t i = 1; i < renderer2DData.textureSlotIndex; i++) {
				if (renderer2DData.textureSlots[i] == texture) {
					textureIndex = static_cast<float>(i);
					break;
				}
			}
			if (textureIndex == 0.0f) {
				textureIndex = static_cast<float>(renderer2DData.textureSlotIndex);
				renderer2DData.textureSlots[renderer2DData.textureSlotIndex]=texture;
				renderer2DData.textureSlotIndex++;
			}

			renderer2DData.quadVertexBufferPtr->position = { position.x + size.x, position.y + size.y, position.z };
			renderer2DData.quadVertexBufferPtr->color = quadColor;
			renderer2DData.quadVertexBufferPtr->textureCoords = { 1.0f, 1.0f };
			renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
			renderer2DData.quadVertexBufferPtr++;

			renderer2DData.quadVertexBufferPtr->position = { position.x + size.x, position.y, position.z };
			renderer2DData.quadVertexBufferPtr->color = quadColor;
			renderer2DData.quadVertexBufferPtr->textureCoords = { 1.0f, 0.0f };
			renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
			renderer2DData.quadVertexBufferPtr++;

			renderer2DData.quadVertexBufferPtr->position = position;
			renderer2DData.quadVertexBufferPtr->color = quadColor;
			renderer2DData.quadVertexBufferPtr->textureCoords = { 0.0f, 0.0f };
			renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
			renderer2DData.quadVertexBufferPtr++;

			renderer2DData.quadVertexBufferPtr->position = { position.x, position.y + size.y, position.z };
			renderer2DData.quadVertexBufferPtr->color = quadColor;
			renderer2DData.quadVertexBufferPtr->textureCoords = { 0.0f, 1.0f };
			renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
			renderer2DData.quadVertexBufferPtr++;

			renderer2DData.quadIndexCount += 6;
		}

		void Renderer2D::DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint) {
			 
		}

		void Renderer2D::BeginBatch() {
			renderer2DData.quadVertexBufferPtr = renderer2DData.quadVertexBufferBase;
			renderer2DData.quadIndexCount = 0;
			renderer2DData.textureSlotIndex = 1;
		}

		void Renderer2D::Flush() {
			std::uint32_t dataSize = static_cast<std::uint32_t>(reinterpret_cast<std::uint8_t*>(renderer2DData.quadVertexBufferPtr) - reinterpret_cast<std::uint8_t*>(renderer2DData.quadVertexBufferBase));
			renderer2DData.quadVertexBuffer->setData(renderer2DData.quadVertexBufferBase, dataSize);

			for (std::uint32_t i = 0; i < renderer2DData.textureSlotIndex; i++) {
				renderer2DData.textureSlots[i]->bind(i);
			}

			RenderCommand::DrawIndexed(renderer2DData.quadVertexArray, renderer2DData.quadIndexCount);
			s_NumberOfDrawCalls++;
		}
	}
}