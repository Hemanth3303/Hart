#pragma once

#include "HartPch.hpp"
#include "RenderCommand.hpp"

namespace Hart {
	namespace Graphics {
		class Renderer2D {
		public:
			static void BeginScene(); //TODO: Add scene parameters
			static void EndScene();

			static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		};
	}
}