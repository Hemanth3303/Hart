#pragma once

#include "HartPch.hpp"
#include "Buffer.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class VertexArray {
		public:
			VertexArray();
			~VertexArray();

			void bind() const;
			void unbind() const;

			void addBuffer(const Buffer& buffer, uint32_t index);
		private:
			uint32_t m_ArrayID = 0;
		};
	}
}