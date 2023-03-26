#pragma once

#include "HartPch.hpp"
#include "VertexArray.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class RenderCommand {
		public:
			static void SetClearColor(const Maths::Vec4& color);
			static void Clear();

			static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
		};
	}
}