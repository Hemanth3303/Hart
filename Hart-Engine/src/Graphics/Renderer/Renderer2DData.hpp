#pragma once

#include "HartPch.hpp"
#include "Maths/Mat4.hpp"
#include "Vertices.hpp"
#include "../VertexBuffer.hpp"
#include "../IndexBuffer.hpp"
#include "../VertexArray.hpp"
#include "../Shader.hpp"
#include "../Texture2D.hpp"

namespace Hart {
	struct Renderer2DData {
	public:
		const std::uint32_t MAX_QUADS = 10'000;
		const std::uint32_t MAX_VERTICES = MAX_QUADS * 4;
		const std::uint32_t MAX_INDICES = MAX_QUADS * 6;
		static constexpr std::uint32_t MAX_TEXTURE_SLOTS = 16;
		const std::uint32_t TEXTURE_SLOT_START = 1;
		const std::uint32_t TEXT_TEXTURE_SLOT = 16;

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
		float lineWidth = 2.0f;
		std::shared_ptr<Shader> lineShader;
		std::shared_ptr<VertexArray> lineVertexArray;
		std::shared_ptr<VertexBuffer> lineVertexBuffer;

		std::uint32_t lineVertexCount = 0;
		LineVertex* lineVertexBufferBase = nullptr;
		LineVertex* lineVertexBufferPtr = nullptr;

		// Textures
		std::array<std::shared_ptr<Texture2D>, MAX_TEXTURE_SLOTS> textureSlots;
		std::uint32_t textureSlotIndex = TEXTURE_SLOT_START; // slot_0 == white texture

		struct Stats {
		public:
			std::uint32_t numberOfDrawCalls = 0;
			std::uint32_t numberOfQuads = 0;
			std::uint32_t numberOfLines = 0;
		public:
			std::uint32_t getQuadVertexCount() const { return numberOfQuads * 4; }
			std::uint32_t getQuadIndexCount() const { return numberOfQuads * 6; }

			std::uint32_t getLineVertexCount() const { return numberOfLines * 2; }
		};
		Stats stats;
	};
}