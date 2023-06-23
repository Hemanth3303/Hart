#pragma once

#include "HartPch.hpp"
#include "../Primitives/VertexArray.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class RenderCommand {
		public:
			static void Init();

			// rgba values in range 0 to 255
			static void SetClearColor(const Maths::Vec4& color);
			static void Clear();
			static void SetViewPort(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height);

			static void DrawArrays(std::uint32_t vertexCount);
			static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
		};
	}
}