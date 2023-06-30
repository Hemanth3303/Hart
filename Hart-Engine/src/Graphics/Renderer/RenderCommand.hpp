#pragma once

#include "HartPch.hpp"
#include "../Primitives/VertexArray.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class RenderCommand {
		public:
			static void Init();
			static void DeInit();

			// rgba values in range 0 to 255
			static void SetClearColor(const Maths::Vec4& color);
			static void Clear();
			static void SetViewPort(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height);
			static std::int64_t getMaxTextureSlotsPerShader();
			static const std::int64_t getMaxTextureSlotsTotal();

			static void DrawArrays(std::uint32_t vertexCount);
			// by default uses index count of index buffer in vertex array
			// if provided with an indexCount > 0, it uses that indexCount instead
			static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, std::uint32_t indexCount = 0);
		};
	}
}