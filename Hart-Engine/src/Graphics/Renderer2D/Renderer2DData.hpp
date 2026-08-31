#pragma once

#include "Maths/Mat4.hpp"
#include "Vertices.hpp"
#include "Graphics/OpenGL/VertexBuffer.hpp"
#include "Graphics/OpenGL/IndexBuffer.hpp"
#include "Graphics/OpenGL/VertexArray.hpp"
#include "Graphics/OpenGL/Shader.hpp"
#include "Graphics/OpenGL/Texture2D.hpp"
#include "Graphics/Font.hpp"

#include "stb_truetype.h"

#include <memory>

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
		std::shared_ptr<FrameBuffer> currentFBO = nullptr;
		Vec2 viewPortDimensions{ 0.0f, 0.0f };

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
		std::shared_ptr<Font> textFont = nullptr;
		std::shared_ptr<Shader> textShader = nullptr;
		std::shared_ptr<VertexArray> textVertexArray = nullptr;
		std::shared_ptr<VertexBuffer> textVertexBuffer = nullptr;

		uint32_t textIndexCount = 0;
		TextVertex* textVertexBufferBase = nullptr;
		TextVertex* textVertexBufferPtr = nullptr;

		std::array<Vec4, VERTICES_PER_QUAD> textVertexPositions;
		std::array<Vec2, VERTICES_PER_QUAD> textTextureCoords;

		float textYAxisSign = 1.0f;
	};
}
