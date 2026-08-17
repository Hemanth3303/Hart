#pragma once

#include "HartPch.hpp"
#include "Maths/Mat4.hpp"
#include "Vertices.hpp"
#include "../VertexBuffer.hpp"
#include "../IndexBuffer.hpp"
#include "../VertexArray.hpp"
#include "../Shader.hpp"
#include "../Texture2D.hpp"
#include "../Font.hpp"

#include "stb_truetype.h"

namespace Hart {
	struct Renderer2DData {
	public:
		const std::uint32_t MAX_QUADS = 10'000;
		const std::uint32_t MAX_VERTICES = MAX_QUADS * 4;
		const std::uint32_t MAX_INDICES = MAX_QUADS * 6;
		static constexpr std::uint32_t MAX_TOTAL_TEXTURE_SLOTS = 16;
		static constexpr std::uint32_t MAX_COMMON_TEXTURE_SLOTS = 15;
		const std::uint32_t WHITE_TEXTURE_SLOT = 0;
		const std::uint32_t COMMON_TEXTURE_SLOT_START = 1; // slot_0 == white texture
		const std::uint32_t TEXT_TEXTURE_SLOT = 15;

		Mat4 viewProjectionMatrix;
		std::shared_ptr<Texture2D> whiteTexture;
		std::shared_ptr<Texture2D> textTexture;

		// Quads
		std::shared_ptr<Shader> quadShader;
		std::shared_ptr<VertexArray> quadVertexArray;
		std::shared_ptr<VertexBuffer> quadVertexBuffer;

		std::uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;

		static constexpr std::uint32_t VERTICES_PER_QUAD = 4;
		std::array<Vec4, VERTICES_PER_QUAD> quadVertexPositions;
		std::array<Vec2, VERTICES_PER_QUAD> quadTextureCoords;

		// Lines
		static constexpr float LINE_THICKNESS_SCALE_FACTOR = 0.005f;

		// Textures
		std::array<std::shared_ptr<Texture2D>, MAX_TOTAL_TEXTURE_SLOTS> textureSlots;
		std::uint32_t textureSlotIndex = COMMON_TEXTURE_SLOT_START;

		// Text
		std::shared_ptr<Font> textFont;
		std::shared_ptr<Shader> textShader;
		std::shared_ptr<VertexArray> textVertexArray;
		std::shared_ptr<VertexBuffer> textVertexBuffer;

		std::uint32_t textIndexCount = 0;
		TextVertex* textVertexBufferBase = nullptr;
		TextVertex* textVertexBufferPtr = nullptr;

		std::array<Vec4, VERTICES_PER_QUAD> textVertexPositions;
		std::array<Vec2, VERTICES_PER_QUAD> textTextureCoords;

		float textPixelScale;

		struct Stats {
		public:
			std::uint32_t numberOfDrawCalls = 0;
			std::uint32_t numberOfQuads = 0;
			std::uint32_t numberOfTextQuads = 0;

		public:
			std::uint32_t getQuadVertexCount() const { return numberOfQuads * 4; }
			std::uint32_t getQuadIndexCount() const { return numberOfQuads * 6; }
			std::uint32_t getTextVertexCount() const { return numberOfTextQuads * 4; }
			std::uint32_t getTextIndexCount() const { return numberOfTextQuads * 6; }
		};
		Stats stats;
	};
}
