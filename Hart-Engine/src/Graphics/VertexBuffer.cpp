#include "HartPch.hpp"
#include "VertexBuffer.hpp"

namespace Hart {
	namespace Graphics {
		VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
			glCreateBuffers(1, &m_ID);
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		VertexBuffer::~VertexBuffer() {
			glDeleteBuffers(1, &m_ID);
		}

		void VertexBuffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		}

		void VertexBuffer::unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}