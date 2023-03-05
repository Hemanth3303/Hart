#pragma once

#include "HartPch.hpp"
#include "Renderer2D.hpp"

namespace Hart {
	namespace Graphics {
		class BatchRenderer2D : public Renderer2D {
		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			virtual void begin() override;

			virtual void submit(const Renderable2D* renderable) override;
			virtual void flush() override;

			virtual void end() override;
		private:
			VertexArray m_VertexArray;
			VertexBuffer m_VertexBuffer;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			int32_t m_IndexCount;
			VertexData* m_Buffer;

			const uint32_t RENDERER_MAX_SPRITES = 60'000;
			const uint32_t RENDERER_VERTEX_SIZE = sizeof(VertexData);
			const uint32_t RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 4;
			const uint32_t RENDERER_BUFFER_SIZE = (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES);
			const uint32_t RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 6;
			const uint32_t SHADER_VERTEX_INDEX = 0;
			const uint32_t SHADER_COLOR_INDEX = 1;
		private:
			void init();
		};
	}
}