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

			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;

		private:
			GLuint m_ArrayId = 0;
			std::vector<Buffer*> m_Buffers;
		};
	}
}