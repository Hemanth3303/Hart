#pragma once

#include "Maths/Mat4.hpp"
#include "Vertices.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/Font.hpp"

#include "stb_truetype.h"

namespace Hart {
	struct Renderer2DData {
	public:
		const uint32_t MAX_QUADS = 10'000;
		const uint32_t MAX_VERTICES = MAX_QUADS * 4;
		const uint32_t MAX_INDICES = MAX_QUADS * 6;
		static constexpr uint32_t MAX_TOTAL_TEXTURE_SLOTS = 16;
		static constexpr uint32_t MAX_COMMON_TEXTURE_SLOTS = 15;
		const uint32_t WHITE_TEXTURE_SLOT = 0;
		const uint32_t COMMON_TEXTURE_SLOT_START = 1; // slot_0 == white texture
		const uint32_t TEXT_TEXTURE_SLOT = 15;

		Mat4 viewProjectionMatrix;

		// Quads
		std::shared_ptr<Shader> quadShader;
		std::shared_ptr<VertexArray> quadVertexArray;
		std::shared_ptr<VertexBuffer> quadVertexBuffer;

		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;

		static constexpr uint32_t VERTICES_PER_QUAD = 4;
		std::array<Vec4, VERTICES_PER_QUAD> quadVertexPositions;
		std::array<Vec2, VERTICES_PER_QUAD> quadTextureCoords;

		// Lines
		static constexpr float LINE_THICKNESS_SCALE_FACTOR = 0.005f;

		// Textures
		std::shared_ptr<Texture2D> whiteTexture;
		std::shared_ptr<Texture2D> textTexture;
		std::array<std::byte, 4> whiteTextureData = {
			std::byte{ 0xff },
			std::byte{ 0xff },
			std::byte{ 0xff },
			std::byte{ 0xff }
		};
		Texture2DSpecification whiteTextureSpec = {
			.width = 1,
			.height = 1,
			.numberOfChannels = 4,
		};
		std::array<std::shared_ptr<Texture2D>, MAX_TOTAL_TEXTURE_SLOTS> textureSlots;
		uint32_t textureSlotIndex = COMMON_TEXTURE_SLOT_START;

		// Text
		std::shared_ptr<Font> textFont;
		std::shared_ptr<Shader> textShader;
		std::shared_ptr<VertexArray> textVertexArray;
		std::shared_ptr<VertexBuffer> textVertexBuffer;

		uint32_t textIndexCount = 0;
		TextVertex* textVertexBufferBase = nullptr;
		TextVertex* textVertexBufferPtr = nullptr;

		std::array<Vec4, VERTICES_PER_QUAD> textVertexPositions;
		std::array<Vec2, VERTICES_PER_QUAD> textTextureCoords;

		float textPixelScale;

		struct Stats {
		public:
			uint32_t numberOfDrawCalls = 0;
			uint32_t numberOfQuads = 0;
			uint32_t numberOfTextQuads = 0;

		public:
			uint32_t getQuadVertexCount() const { return numberOfQuads * 4; }
			uint32_t getQuadIndexCount() const { return numberOfQuads * 6; }
			uint32_t getTextVertexCount() const { return numberOfTextQuads * 4; }
			uint32_t getTextIndexCount() const { return numberOfTextQuads * 6; }
		};
		Stats stats;
	};
}
