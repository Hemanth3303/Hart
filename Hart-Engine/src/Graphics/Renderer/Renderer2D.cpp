#include "HartPch.hpp"
#include "Renderer2D.hpp"
#include "Renderer2DData.hpp"
#include "RenderCommand.hpp"
#include "Core/Application.hpp"

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

		s_Data->quadVertexArray->getIndexBuffer()->unbind();
		s_Data->quadVertexArray->unbind();
		s_Data->quadShader->unbind();

	}

	void Renderer2D::BeginScene(OrthographicCamera& camera) {
		s_Data->viewProjectionMatrix = camera.getViewProjectionMatrix();

		HART_ASSERT_NOT_EQUAL(s_Data->quadShader, nullptr, "Reason: quadShader is not initialized");
		HART_ASSERT_NOT_EQUAL(s_Data->quadVertexArray, nullptr, "Reason: quadVertexArray is not initialized");

		s_Data->quadShader->bind();
		s_Data->quadShader->setUniform("uViewProjectionMatrix2D", s_Data->viewProjectionMatrix);

		BeginBatch();
	}

	void Renderer2D::EndScene() {
		Flush();
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const Vec4& color) {
		DrawQuad(position, size, 0.0f, color);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, float angleD, const Vec4& color) {
		Mat4 transform = Mat4::Translate(position) * Mat4::Rotate(angleD, { 0.0f, 0.0f, 1.0f }) * Mat4::Scale({ size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const std::shared_ptr<Texture2D>& texture, const Vec4& textureTint, float tilingFactor) {
		DrawQuad(position, size, 0.0f, texture, textureTint, tilingFactor);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Vec4& textureTint, float tilingFactor) {
		Mat4 transform = Mat4::Translate(position) * Mat4::Rotate(angleD, { 0.0f, 0.0f, 1.0f }) * Mat4::Scale({ size.x, size.y, 1.0f });
		
		DrawQuad(transform, texture, textureTint, tilingFactor);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const std::shared_ptr<SpriteSheet>& spriteSheet, const Vec2& subTextureIndex, const Vec4& textureTint) {
		DrawQuad(position, size, 0.0f, spriteSheet, subTextureIndex, textureTint);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, float angleD, const std::shared_ptr<SpriteSheet>& spriteSheet, const Vec2& subTextureIndex, const Vec4& textureTint) {
		Mat4 transform = Mat4::Translate(position) * Mat4::Rotate(angleD, { 0.0f, 0.0f, 1.0f }) * Mat4::Scale({ size.x, size.y, 1.0f });

		DrawQuad(transform, spriteSheet, subTextureIndex, textureTint);
	}

	void Renderer2D::DrawQuad(const Mat4& transform, const Vec4& color) {
		if ((s_Data->textureSlotIndex >= s_Data->MAX_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
			Flush();
			BeginBatch();
		}

		s_Data->quadTextureCoords[0] = { 0.0f, 0.0f };
		s_Data->quadTextureCoords[1] = { 1.0f, 0.0f };
		s_Data->quadTextureCoords[2] = { 1.0f, 1.0f };
		s_Data->quadTextureCoords[3] = { 0.0f, 1.0f };

		AddNewQuadVertex(transform, color, 0.0f, 1.0f);
	}

	void Renderer2D::DrawQuad(const Mat4& transform, const std::shared_ptr<Texture2D>& texture, const Vec4& textureTint, float tilingFactor) {
		if ((s_Data->textureSlotIndex >= s_Data->MAX_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
			Flush();
			BeginBatch();
		}

		float textureIndex = CalculateTextureIndex(texture);

		s_Data->quadTextureCoords[0] = { 0.0f, 0.0f };
		s_Data->quadTextureCoords[1] = { 1.0f, 0.0f };
		s_Data->quadTextureCoords[2] = { 1.0f, 1.0f };
		s_Data->quadTextureCoords[3] = { 0.0f, 1.0f };

		AddNewQuadVertex(transform, textureTint, textureIndex, tilingFactor);
	}

	void Renderer2D::DrawQuad(const Mat4& transform, const std::shared_ptr<SpriteSheet>& spriteSheet, const Vec2& subTextureIndex, const Vec4& textureTint) {
		if ((s_Data->textureSlotIndex >= s_Data->MAX_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
			Flush();
			BeginBatch();
		}

		float textureIndex = CalculateTextureIndex(spriteSheet->getTexture());

		const auto& [sheetWidth, sheetHeight] = spriteSheet->getSpriteSheetSize();
		const auto& [spriteWidth, spriteHeight] = spriteSheet->getSpriteSize();

		float numberOfRows = (sheetHeight / spriteHeight);
		float x = subTextureIndex.x;
		float y = numberOfRows - subTextureIndex.y - 1.0f;

		s_Data->quadTextureCoords[0] = { (x + 0) * spriteWidth / sheetWidth, (y + 0) * spriteHeight / sheetHeight };
		s_Data->quadTextureCoords[1] = { (x + 1) * spriteWidth / sheetWidth, (y + 0) * spriteHeight / sheetHeight };
		s_Data->quadTextureCoords[2] = { (x + 1) * spriteWidth / sheetWidth, (y + 1) * spriteHeight / sheetHeight };
		s_Data->quadTextureCoords[3] = { (x + 0) * spriteWidth / sheetWidth, (y + 1) * spriteHeight / sheetHeight };

		AddNewQuadVertex(transform, textureTint, textureIndex, 1.0f);
	}

	void Renderer2D::DrawLine(const Vec3& startPosition, const Vec3& endPosition, const Vec4& color, const float thickness) {
		Vec3 midpoint = { (startPosition.x + endPosition.x) / 2.0f, (startPosition.y + endPosition.y) / 2.0f };
		Vec3 direction = endPosition - startPosition;
		float length = direction.getMagnitude();
		Vec2 size = { length,  thickness * s_Data->LINE_THICKNESS_SCALE_FACTOR };
		float angleD = arcTan2D(-direction.y, direction.x);

		DrawQuad(midpoint, size, angleD, color);
	}


	void Renderer2D::DrawText(const std::string& text, const Vec3& position, float size, const Vec4& color) {
		DrawText(text, position, size, 0.0f, color);
	}

	void Renderer2D::DrawText(const std::string& text, const Vec3& position, float size, float angleD, const Vec4& color) {
		Mat4 transform = Mat4::Translate(position) * Mat4::Rotate(angleD, { 0.0f, 0.0f, 1.0f }) * Mat4::Scale({ size, size, 1.0f });

		DrawText(text, transform, color);
	}

	void Renderer2D::DrawText(const std::string& text, const Mat4& transform, const Vec4& color) {
		// if some conditions
		//	Flush();
		//	BeginBatch();
		// AddNewTextVertex(params);
	}

	void Renderer2D::ResetStats() {
		s_Data->stats.numberOfDrawCalls = 0;
		s_Data->stats.numberOfQuads = 0;
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


	void Renderer2D::BeginBatch() {
		// Quads
		s_Data->quadVertexBufferPtr = s_Data->quadVertexBufferBase;
		s_Data->quadIndexCount = 0;

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
			std::uint8_t* quadVertBase = reinterpret_cast<std::uint8_t*>(s_Data->quadVertexBufferBase);
			std::uint8_t* quadVertPtr = reinterpret_cast<std::uint8_t*>(s_Data->quadVertexBufferPtr);
			std::uint32_t dataSize = static_cast<std::uint32_t>(quadVertPtr-quadVertBase);

			s_Data->quadVertexBuffer->setData(s_Data->quadVertexBufferBase, dataSize);

			s_Data->quadShader->bind();
			RenderCommand::DrawIndexed(s_Data->quadVertexArray, s_Data->quadIndexCount);

			s_Data->stats.numberOfDrawCalls++;
		}
	}

	const float Renderer2D::CalculateTextureIndex(const std::shared_ptr<Texture2D>& texture) {
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

		return textureIndex;
	}

	void Renderer2D::AddNewQuadVertex(const Mat4& transform, const Vec4& color, float textureIndex, float tiliingFactor) {
		for (std::size_t i = 0; i < s_Data->VERTICES_PER_QUAD; i++) {
			s_Data->quadVertexBufferPtr->position = transform * s_Data->quadVertexPositions[i];
			s_Data->quadVertexBufferPtr->color = color;
			s_Data->quadVertexBufferPtr->textureCoords = s_Data->quadTextureCoords[i];
			s_Data->quadVertexBufferPtr->textureIndex = textureIndex;
			s_Data->quadVertexBufferPtr->tilingFactor = tiliingFactor;
			s_Data->quadVertexBufferPtr++;
		}

		s_Data->quadIndexCount += 6;

		s_Data->stats.numberOfQuads++;
	}
}