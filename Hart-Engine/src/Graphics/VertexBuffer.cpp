#include "HartPch.hpp"
#include "VertexBuffer.hpp"

namespace Hart {
	namespace Graphics {
		VertexBuffer::VertexBuffer() {
			glGenBuffers(1, &m_ID);
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