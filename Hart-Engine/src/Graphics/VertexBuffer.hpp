#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class VertexBuffer {
		public:
			VertexBuffer(float* vertices, uint32_t size);
			~VertexBuffer();

			void bind() const;
			void unbind() const;
		private:
			uint32_t m_ID;
		};
	}
}