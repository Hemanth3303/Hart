#include "HartPch.hpp"
#include "Renderer2D.hpp"
#include "Renderer2DData.hpp"
#include "RenderCommand.hpp"
#include "Core/HartApplication.hpp"

namespace Hart {
	static std::unique_ptr<Renderer2DData> s_Data;

	void Renderer2D::Init() {
		HART_ENGINE_LOG("Initializing Renderer2D");

		s_Data = std::make_unique<Renderer2DData>();
		HART_ASSERT_NOT_EQUAL(s_Data, nullptr, "Reason: Failed to initialize Renderer2D");

		// Quads
		std::vector<std::uint32_t> quadIndices;
		quadIndices.resize(s_Data->MAX_INDICES);

		std::uint32_t offset = 0;
		for (std::size_t i = 0; i < s_Data->MAX_INDICES; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		BufferLayout quadBufferLayout = {
			{ ShaderDataType::Float4, "aPosition" },
			{ ShaderDataType::Float4, "aColor" },
			{ ShaderDataType::Float2, "aTextureCoords" },
			{ ShaderDataType::Float,  "aTextureIndex" },
			{ ShaderDataType::Float,  "aTilingFactor" }
		};

		s_Data->quadShader = Application::Get()->getShader("QuadShader2D");

		s_Data->quadVertexArray = std::make_shared<VertexArray>();
		s_Data->quadVertexArray->bind();

		s_Data->quadVertexBuffer = std::make_shared<VertexBuffer>(s_Data->MAX_VERTICES * static_cast<std::uint32_t>(sizeof(QuadVertex)));
		s_Data->quadVertexBuffer->setLayout(quadBufferLayout);
		s_Data->quadVertexArray->setVertexBuffer(s_Data->quadVertexBuffer);

		s_Data->quadVertexBufferBase = new QuadVertex[s_Data->MAX_VERTICES];

		std::shared_ptr<IndexBuffer> quadIndexBuffer = std::make_shared<IndexBuffer>(quadIndices.data(), s_Data->MAX_INDICES);
		s_Data->quadVertexArray->setIndexBuffer(quadIndexBuffer);

		s_Data->quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->quadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data->quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		// Lines
		RenderCommand::EnableSmoothLines();
		s_Data->lineShader = Application::Get()->getShader("LineShader2D");
		s_Data->lineVertexArray = std::make_shared<VertexArray>();
		s_Data->lineVertexArray->bind();

		BufferLayout lineBufferLayout = {
			{ ShaderDataType::Float4, "aPosition" },
			{ ShaderDataType::Float4, "aColor" }
		};

		s_Data->lineVertexBuffer = std::make_shared<VertexBuffer>(s_Data->MAX_VERTICES * static_cast<std::uint32_t>(sizeof(LineVertex)));
		s_Data->lineVertexBuffer->setLayout(lineBufferLayout);
		s_Data->lineVertexArray->setVertexBuffer(s_Data->lineVertexBuffer);
		s_Data->lineVertexBufferBase = new LineVertex[s_Data->MAX_VERTICES];

		// White Texture
		std::uint32_t whiteTextureData = 0xffffffff;
		Texture2DSpecification whiteTextureSpec;
		whiteTextureSpec.width = 1;
		whiteTextureSpec.height = 1;
		whiteTextureSpec.numberOfChannels = 4;
		s_Data->whiteTexture = std::make_shared<Texture2D>(&whiteTextureData, whiteTextureSpec);
		s_Data->textureSlots[0] = s_Data->whiteTexture;

		s_Data->quadShader->bind();
		s_Data->quadShader->setUniform("uTexture0", s_Data->textureSlots[0]->getSlot());
	}

	void Renderer2D::DeInit() {
		HART_ENGINE_LOG("DeInitializing Renderer2D");

		delete s_Data->quadVertexBufferBase;
		delete s_Data->lineVertexBufferBase;

		s_Data->quadVertexArray->getIndexBuffer()->unbind();
		s_Data->quadVertexArray->unbind();
		s_Data->quadShader->unbind();

		s_Data->lineVertexArray->unbind();
		s_Data->lineShader->unbind();
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera) {
		s_Data->viewProjectionMatrix = camera.getViewProjectionMatrix();

		HART_ASSERT_NOT_EQUAL(s_Data->quadShader, nullptr, "Reason: quadShader is not initialized");
		HART_ASSERT_NOT_EQUAL(s_Data->quadVertexArray, nullptr, "Reason: quadVertexArray is not initialized");

		HART_ASSERT_NOT_EQUAL(s_Data->lineShader, nullptr, "Reason: lineShader is not initialized");
		HART_ASSERT_NOT_EQUAL(s_Data->lineVertexArray, nullptr, "Reason: lineVertexArray is not initialized");

		s_Data->quadShader->bind();
		s_Data->quadShader->setUniform("uViewProjectionMatrix2D", s_Data->viewProjectionMatrix);

		s_Data->lineShader->bind();
		s_Data->lineShader->setUniform("uViewProjectionMatrix2D", s_Data->viewProjectionMatrix);

		BeginBatch();
	}

	void Renderer2D::EndScene() {
		Flush();
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const Vec4& color) {
		DrawQuad(position, size, 0.0f, color);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, float angleD, const Vec4& color) {
		if ((s_Data->textureSlotIndex >= s_Data->MAX_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
			Flush();
			BeginBatch();
		}

		s_Data->quadTextureCoords[0] = { 0.0f, 0.0f };
		s_Data->quadTextureCoords[1] = { 1.0f, 0.0f };
		s_Data->quadTextureCoords[2] = { 1.0f, 1.0f };
		s_Data->quadTextureCoords[3] = { 0.0f, 1.0f };

		AddNewQuadVertex(position, size, angleD, color, 0.0f, 1.0f);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const std::shared_ptr<Texture2D>& texture, const Vec4& textureTint, float tilingFactor) {
		DrawQuad(position, size, 0.0f, texture, textureTint, tilingFactor);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Vec4& textureTint, float tilingFactor) {
		if ((s_Data->textureSlotIndex >= s_Data->MAX_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
			Flush();
			BeginBatch();
		}

		float textureIndex = 0.0f;

		for (std::size_t i = s_Data->TEXTURE_SLOT_START; i < s_Data->textureSlotIndex; i++) {
			if (s_Data->textureSlots[i] == texture) {
				textureIndex = static_cast<float>(i);
				break;
			}
		}
		if (textureIndex == 0.0f) {
			textureIndex = static_cast<float>(s_Data->textureSlotIndex);
			if (s_Data->textureSlotIndex >= s_Data->TEXTURE_SLOT_START && s_Data->textureSlotIndex < s_Data->MAX_TEXTURE_SLOTS) {
				s_Data->textureSlots[s_Data->textureSlotIndex] = texture;
			}
			s_Data->textureSlotIndex++;
		}

		s_Data->quadTextureCoords[0] = { 0.0f, 0.0f };
		s_Data->quadTextureCoords[1] = { 1.0f, 0.0f };
		s_Data->quadTextureCoords[2] = { 1.0f, 1.0f };
		s_Data->quadTextureCoords[3] = { 0.0f, 1.0f };

		AddNewQuadVertex(position, size, angleD, textureTint, textureIndex, tilingFactor);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const std::shared_ptr<SpriteSheet>& spriteSheet, const Vec2& subTextureIndex, const Vec4& textureTint) {
		DrawQuad(position, size, 0.0f, spriteSheet, subTextureIndex, textureTint);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, float angleD, const std::shared_ptr<SpriteSheet>& spriteSheet, const Vec2& subTextureIndex, const Vec4& textureTint) {
		if ((s_Data->textureSlotIndex >= s_Data->MAX_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
			Flush();
			BeginBatch();
		}

		float textureIndex = 0.0f;

		for (std::size_t i = s_Data->TEXTURE_SLOT_START; i < s_Data->textureSlotIndex; i++) {
			if (s_Data->textureSlots[i] == spriteSheet->getTexture()) {
				textureIndex = static_cast<float>(i);
				break;
			}
		}
		if (textureIndex == 0.0f) {
			textureIndex = static_cast<float>(s_Data->textureSlotIndex);
			if (s_Data->textureSlotIndex >= s_Data->TEXTURE_SLOT_START && s_Data->textureSlotIndex < s_Data->MAX_TEXTURE_SLOTS) {
				s_Data->textureSlots[s_Data->textureSlotIndex] = spriteSheet->getTexture();
			}
			s_Data->textureSlotIndex++;
		}

		const auto& [sheetWidth, sheetHeight] = spriteSheet->getSpriteSheetSize();
		const auto& [spriteWidth, spriteHeight] = spriteSheet->getSpriteSize();

		float numberOfRows = (sheetHeight / spriteHeight);
		float x = subTextureIndex.x;
		float y = numberOfRows - subTextureIndex.y - 1.0f;

		s_Data->quadTextureCoords[0] = { (x + 0) * spriteWidth / sheetWidth, (y + 0) * spriteHeight / sheetHeight };
		s_Data->quadTextureCoords[1] = { (x + 1) * spriteWidth / sheetWidth, (y + 0) * spriteHeight / sheetHeight };
		s_Data->quadTextureCoords[2] = { (x + 1) * spriteWidth / sheetWidth, (y + 1) * spriteHeight / sheetHeight };
		s_Data->quadTextureCoords[3] = { (x + 0) * spriteWidth / sheetWidth, (y + 1) * spriteHeight / sheetHeight };

		AddNewQuadVertex(position, size, angleD, textureTint, textureIndex, 1.0f);
	}

	void Renderer2D::SetLineWidth(float width) {
		s_Data->lineWidth = width;
	}

	void Renderer2D::DrawLine(const Vec3& startPosition, const Vec3& endPosition, const Vec4& color) {
		if (s_Data->lineVertexCount >= s_Data->MAX_VERTICES) {
			Flush();
			BeginBatch();
		}

		AddNewLineVertex(startPosition, endPosition, color);
	}

	void Renderer2D::DrawText(const std::string& text, const Vec3& position, float size, const Vec4& color) {
		
	}

	void Renderer2D::ResetStats() {
		s_Data->stats.numberOfDrawCalls = 0;
		s_Data->stats.numberOfQuads = 0;
		s_Data->stats.numberOfLines = 0;
	}

	std::uint32_t Renderer2D::GetNumberOfDrawCalls() {
		return s_Data->stats.numberOfDrawCalls;
	}

	std::uint32_t Renderer2D::GetNumberOfQuads() {
		return s_Data->stats.numberOfQuads;
	}

	std::uint32_t Renderer2D::GetNumberOfQuadVertices() {
		return s_Data->stats.getQuadVertexCount();
	}

	std::uint32_t Renderer2D::GetNumberOfQuadIndices() {
		return s_Data->stats.getQuadIndexCount();
	}

	std::uint32_t Renderer2D::GetNumberOfLines() {
		return s_Data->stats.numberOfLines;
	}

	std::uint32_t Renderer2D::GetNumberOfLineVertices() {
		return s_Data->stats.getLineVertexCount();
	}

	void Renderer2D::BeginBatch() {
		// Quads
		s_Data->quadVertexBufferPtr = s_Data->quadVertexBufferBase;
		s_Data->quadIndexCount = 0;

		// Lines
		s_Data->lineVertexBufferPtr = s_Data->lineVertexBufferBase;
		s_Data->lineVertexCount = 0;

		// Textures
		s_Data->textureSlotIndex = s_Data->TEXTURE_SLOT_START;
	}

	void Renderer2D::Flush() {
		for (std::uint32_t i = 0; i < s_Data->textureSlotIndex; i++) {
			s_Data->quadShader->bind();
			s_Data->textureSlots[i]->bind(i);
			s_Data->quadShader->setUniform("uTexture" + std::to_string(i), s_Data->textureSlots[i]->getSlot());
		}

		// Quads
		if (s_Data->quadIndexCount != 0) {
			std::uint32_t dataSize = static_cast<std::uint32_t>(reinterpret_cast<std::uint8_t*>(s_Data->quadVertexBufferPtr) - reinterpret_cast<std::uint8_t*>(s_Data->quadVertexBufferBase));
			s_Data->quadVertexBuffer->setData(s_Data->quadVertexBufferBase, dataSize);

			s_Data->quadShader->bind();
			RenderCommand::DrawIndexed(s_Data->quadVertexArray, s_Data->quadIndexCount);

			s_Data->stats.numberOfDrawCalls++;
		}

		// Lines
		if (s_Data->lineVertexCount != 0) {
			std::uint32_t dataSize = static_cast<std::uint32_t>(reinterpret_cast<std::uint8_t*>(s_Data->lineVertexBufferPtr) - reinterpret_cast<std::uint8_t*>(s_Data->lineVertexBufferBase));
			s_Data->lineVertexBuffer->setData(s_Data->lineVertexBufferBase, dataSize);

			s_Data->lineShader->bind();
			RenderCommand::SetLineWidth(s_Data->lineWidth);
			RenderCommand::DrawLines(s_Data->lineVertexArray, s_Data->lineVertexCount);

			s_Data->stats.numberOfDrawCalls++;
		}
	}

	void Renderer2D::AddNewQuadVertex(const Vec3& position, const Vec2& size, float angleD, const Vec4& quadColor, float textureIndex, float tiliingFactor) {

		Mat4 transform = Mat4::Translate(position) * Mat4::Rotate(angleD, { 0.0f, 0.0f, 1.0f }) * Mat4::Scale({ size.x, size.y, 1.0f });

		for (std::size_t i = 0; i < s_Data->VERTICES_PER_QUAD; i++) {
			s_Data->quadVertexBufferPtr->position = transform * s_Data->quadVertexPositions[i];
			s_Data->quadVertexBufferPtr->color = quadColor;
			s_Data->quadVertexBufferPtr->textureCoords = s_Data->quadTextureCoords[i];
			s_Data->quadVertexBufferPtr->textureIndex = textureIndex;
			s_Data->quadVertexBufferPtr->tilingFactor = tiliingFactor;
			s_Data->quadVertexBufferPtr++;
		}

		s_Data->quadIndexCount += 6;

		s_Data->stats.numberOfQuads++;
	}

	void Renderer2D::AddNewLineVertex(const Vec3& startPosition, const Vec3& endPosition, const Vec4& color) {
		s_Data->lineVertexBufferPtr->position = Vec4(startPosition, 1.0f);
		s_Data->lineVertexBufferPtr->color = color;
		s_Data->lineVertexBufferPtr++;

		s_Data->lineVertexBufferPtr->position = Vec4(endPosition, 1.0f);
		s_Data->lineVertexBufferPtr->color = color;
		s_Data->lineVertexBufferPtr++;

		s_Data->lineVertexCount += 2;

		s_Data->stats.numberOfLines++;
	}
}