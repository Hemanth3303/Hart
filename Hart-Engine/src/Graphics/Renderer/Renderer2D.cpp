#include "HartPch.hpp"
#include "Renderer2D.hpp"
#include "Renderer2DData.hpp"
#include "RenderCommand.hpp"
#include "Core/Application.hpp"

namespace Hart {
	void recalculateTextPixelScaler();

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

		// use coordinates with (0, 0) at center
		s_Data->quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->quadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data->quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		// Text
		std::vector<std::uint32_t> textIndices;
		textIndices.resize(s_Data->MAX_INDICES);

		std::uint32_t textIndexOffset = 0;
		for (std::size_t i = 0; i < s_Data->MAX_INDICES; i += 6) {
			textIndices[i + 0] = textIndexOffset + 0;
			textIndices[i + 1] = textIndexOffset + 1;
			textIndices[i + 2] = textIndexOffset + 2;

			textIndices[i + 3] = textIndexOffset + 2;
			textIndices[i + 4] = textIndexOffset + 3;
			textIndices[i + 5] = textIndexOffset + 0;

			textIndexOffset += 4;
		}

		BufferLayout textBufferLayout = {
			{ ShaderDataType::Float4, "aPosition" },
			{ ShaderDataType::Float4, "aColor" },
			{ ShaderDataType::Float2, "aTextureCoords" }
		};

		s_Data->textShader = Application::Get()->getShader("TextShader");

		s_Data->textVertexArray = std::make_shared<VertexArray>();
		s_Data->textVertexArray->bind();

		s_Data->textVertexBuffer = std::make_shared<VertexBuffer>(s_Data->MAX_VERTICES * static_cast<std::uint32_t>(sizeof(TextVertex)));
		s_Data->textVertexBuffer->setLayout(textBufferLayout);
		s_Data->textVertexArray->setVertexBuffer(s_Data->textVertexBuffer);

		s_Data->textVertexBufferBase = new TextVertex[s_Data->MAX_VERTICES];

		std::shared_ptr<IndexBuffer> textIndexBuffer = std::make_shared<IndexBuffer>(textIndices.data(), s_Data->MAX_INDICES);
		s_Data->textVertexArray->setIndexBuffer(textIndexBuffer);

		recalculateTextPixelScaler();

		// use coordinates with (0, 0) at center
		s_Data->textVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->textVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->textVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data->textVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		// White Texture
		std::uint32_t whiteTextureData = 0xffffffff;
		Texture2DSpecification whiteTextureSpec;
		whiteTextureSpec.width = 1;
		whiteTextureSpec.height = 1;
		whiteTextureSpec.numberOfChannels = 4;
		s_Data->whiteTexture = std::make_shared<Texture2D>(&whiteTextureData, whiteTextureSpec);
		s_Data->textureSlots[s_Data->WHITE_TEXTURE_SLOT] = s_Data->whiteTexture;

		s_Data->quadShader->bind();
		s_Data->whiteTexture->bind(s_Data->WHITE_TEXTURE_SLOT);
		s_Data->quadShader->setUniform("uTexture0", s_Data->whiteTexture->getSlot());
	}

	void Renderer2D::DeInit() {
		HART_ENGINE_LOG("DeInitializing Renderer2D");

		delete[] s_Data->quadVertexBufferBase;
		delete[] s_Data->textVertexBufferBase;

		s_Data->quadVertexArray->getIndexBuffer()->unbind();
		s_Data->quadVertexArray->unbind();
		s_Data->quadShader->unbind();

		s_Data->textVertexArray->getIndexBuffer()->unbind();
		s_Data->textVertexArray->unbind();
		s_Data->textShader->unbind();

		s_Data.reset();
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera) {
		s_Data->viewProjectionMatrix = camera.getViewProjectionMatrix();

		HART_ASSERT_NOT_EQUAL(s_Data->quadShader, nullptr, "Reason: quadShader is not initialized");
		HART_ASSERT_NOT_EQUAL(s_Data->quadVertexArray, nullptr, "Reason: quadVertexArray is not initialized");

		HART_ASSERT_NOT_EQUAL(s_Data->textShader, nullptr, "Reason: textShader is not initialized");
		HART_ASSERT_NOT_EQUAL(s_Data->textVertexArray, nullptr, "Reason: quadVertexArray is not initialized");

		s_Data->quadShader->bind();
		s_Data->quadShader->setUniform("uViewProjectionMatrix2D", s_Data->viewProjectionMatrix);

		s_Data->textShader->bind();
		s_Data->textShader->setUniform("uViewProjectionMatrix2D", s_Data->viewProjectionMatrix);

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
		if ((s_Data->textureSlotIndex >= s_Data->MAX_COMMON_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
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
		if ((s_Data->textureSlotIndex >= s_Data->MAX_COMMON_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
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
		if ((s_Data->textureSlotIndex >= s_Data->MAX_COMMON_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
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


	void Renderer2D::SetFont(const std::shared_ptr<Font>& font) {
		HART_ASSERT_NOT_EQUAL(font, nullptr);
		s_Data->textFont = font;

		s_Data->textTexture = std::make_shared<Texture2D>(s_Data->textFont->getFontAtlasBitmapData(), s_Data->textFont->getTextureSpecification());

		s_Data->textShader->bind();
		s_Data->textTexture->bind(s_Data->TEXT_TEXTURE_SLOT);
		s_Data->textShader->setUniform("uTexture15", s_Data->textTexture->getSlot());
	}

	void Renderer2D::DrawText(const std::string& text, const Vec3& position, float scaling, const Vec4& color) {
		HART_ASSERT_NOT_EQUAL(s_Data->textFont, nullptr, "Font not set, did you forget to call Hart::Renderer2D::SetFont()");

		recalculateTextPixelScaler();

		stbtt_packedchar* packedChars = s_Data->textFont->getSTBTTPackedChar();
		stbtt_aligned_quad* alignedQuads = s_Data->textFont->getSTBTTAlignedQuads();
		std::uint32_t codePointFirstChar = s_Data->textFont->getCodePointFirstChar();
		std::uint32_t numberOfCharsToInclude = s_Data->textFont->getNumberOfCharsToInclude();

		Vec3 charPos = position;
		for (const char ch : text) {
			if (ch == '\n') {
				charPos.y -= s_Data->textFont->getFontSize() * s_Data->textPixelScale * scaling;
				charPos.x = position.x;
			}
			else if (ch < codePointFirstChar || ch > (codePointFirstChar + numberOfCharsToInclude)) {
				continue;
			}
			else {

				stbtt_packedchar* packedChar = &packedChars[ch - codePointFirstChar];
				stbtt_aligned_quad* alignedQuad = &alignedQuads[ch - codePointFirstChar];

				Vec3 glyphSize = {
					(packedChar->x1 - packedChar->x0) * s_Data->textPixelScale * scaling,
					(packedChar->y1 - packedChar->y0) * s_Data->textPixelScale * scaling,
					1.0f
				};

				Vec3 glyphBoundingBoxBottomLeft = {
					charPos.x + (packedChar->xoff * s_Data->textPixelScale * scaling) + (glyphSize.x / 2.0f),
					charPos.y - (packedChar->yoff + packedChar->y1 - packedChar->y0) * s_Data->textPixelScale * scaling + (glyphSize.y / 2.0f),
					charPos.z
				};

				s_Data->textTextureCoords[0] = { alignedQuad->s0, alignedQuad->t1 };  // Top-left
				s_Data->textTextureCoords[1] = { alignedQuad->s1, alignedQuad->t1 };  // Top-right
				s_Data->textTextureCoords[2] = { alignedQuad->s1, alignedQuad->t0 };  // Bottom-right
				s_Data->textTextureCoords[3] = { alignedQuad->s0, alignedQuad->t0 };  // Bottom-left

				Mat4 transform = Mat4::Translate(glyphBoundingBoxBottomLeft) * Mat4::Scale(glyphSize);

				AddNewTextVertex(transform, color);

				charPos.x += packedChar->xadvance * s_Data->textPixelScale * scaling;
			}
		}
	}

	void Renderer2D::ResetStats() {
		s_Data->stats.numberOfDrawCalls = 0;
		s_Data->stats.numberOfQuads = 0;
		s_Data->stats.numberOfTextQuads = 0;
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

	std::uint32_t Renderer2D::GetNumberOfTextQuads() {
		return s_Data->stats.numberOfTextQuads;
	}

	std::uint32_t Renderer2D::GetNumberOfTextQuadVertices() {
		return s_Data->stats.getTextVertexCount();
	}

	std::uint32_t Renderer2D::GetNumberOfTextQuadIndices() {
		return s_Data->stats.getTextIndexCount();
	}


	void Renderer2D::BeginBatch() {
		// Quads
		s_Data->quadVertexBufferPtr = s_Data->quadVertexBufferBase;
		s_Data->quadIndexCount = 0;

		// Text
		s_Data->textVertexBufferPtr = s_Data->textVertexBufferBase;
		s_Data->textIndexCount = 0;

		// Textures
		s_Data->textureSlotIndex = s_Data->COMMON_TEXTURE_SLOT_START;
	}

	void Renderer2D::Flush() {
		s_Data->quadShader->bind();
		s_Data->whiteTexture->bind(s_Data->WHITE_TEXTURE_SLOT);
		for (std::uint32_t i = s_Data->COMMON_TEXTURE_SLOT_START; i < s_Data->textureSlotIndex; i++) {
			//s_Data->quadShader->bind();
			s_Data->textureSlots[i]->bind(i);
			s_Data->quadShader->setUniform("uTexture" + std::to_string(i), s_Data->textureSlots[i]->getSlot());
		}
		if (s_Data->textFont) {
			s_Data->textShader->bind();
			s_Data->textTexture->bind(s_Data->TEXT_TEXTURE_SLOT);
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

		// Text
		if (s_Data->textIndexCount != 0) {
			std::uint8_t* textVertBase = reinterpret_cast<std::uint8_t*>(s_Data->textVertexBufferBase);
			std::uint8_t* textVertPtr = reinterpret_cast<std::uint8_t*>(s_Data->textVertexBufferPtr);
			std::uint32_t dataSize = static_cast<std::uint32_t>(textVertPtr - textVertBase);

			s_Data->textVertexBuffer->setData(s_Data->textVertexBufferBase, dataSize);

			s_Data->textShader->bind();
			RenderCommand::DrawIndexed(s_Data->textVertexArray, s_Data->textIndexCount);

			s_Data->stats.numberOfDrawCalls++;
		}
	}

	const float Renderer2D::CalculateTextureIndex(const std::shared_ptr<Texture2D>& texture) {
		if ((s_Data->textureSlotIndex >= s_Data->MAX_COMMON_TEXTURE_SLOTS) || (s_Data->quadIndexCount >= s_Data->MAX_INDICES)) {
			Flush();
			BeginBatch();
		}

		float textureIndex = 0.0f;

		for (std::size_t i = s_Data->COMMON_TEXTURE_SLOT_START; i < s_Data->textureSlotIndex; i++) {
			if (s_Data->textureSlots[i] == texture) {
				textureIndex = static_cast<float>(i);
				break;
			}
		}
		if (textureIndex == 0.0f) {
			textureIndex = static_cast<float>(s_Data->textureSlotIndex);
			if (s_Data->textureSlotIndex >= s_Data->COMMON_TEXTURE_SLOT_START && s_Data->textureSlotIndex < s_Data->MAX_COMMON_TEXTURE_SLOTS) {
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

	void Renderer2D::AddNewTextVertex(const Mat4& transform, const Vec4& color) {
		for (std::size_t i = 0; i < s_Data->VERTICES_PER_QUAD; i++) {
			s_Data->textVertexBufferPtr->position = transform * s_Data->textVertexPositions[i];
			s_Data->textVertexBufferPtr->color = color;
			s_Data->textVertexBufferPtr->textureCoords = s_Data->textTextureCoords[i];
			s_Data->textVertexBufferPtr++;
		}
		s_Data->textIndexCount += 6;

		s_Data->stats.numberOfTextQuads++;

	}

	void recalculateTextPixelScaler() {
		float aspectRatio = static_cast<float>(Application::Get()->getWindowHeight()) / static_cast<float>(Application::Get()->getWindowWidth());
		s_Data->textPixelScale = 0.001f / aspectRatio; //TODO: FIX
	}
}