#pragma once

#include "Renderer2D.hpp"
#include "Renderable2D.hpp"
#include "buffers/IndexBuffer.hpp"

namespace Hart {
	namespace Graphics {
		constexpr GLsizei RENDERER_MAX_SPRITES = 60000;
		constexpr GLsizei RENDERER_VERTEX_SIZE = sizeof(VertexData);
		constexpr GLsizei RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 4;
		constexpr GLsizeiptr RENDERER_BUFFER_SIZE = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
		constexpr GLsizei RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 6;

		constexpr GLuint SHADER_VERTEX_INDEX = 0;
		constexpr GLuint SHADER_COLOR_INDEX = 1;

		class BatchRenderer2D : public Renderer2D {
		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;
			void submit(const Renderable2D* renderable2d) override;
			void end() override;
			void flush() override;
		private:
			void init();
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			GLsizei m_IndexCount;
			VertexData* m_Buffer;
			GLuint* m_Indices;
		};
	}
}