#include "HartPch.hpp"
#include "IndexBuffer.hpp"

namespace Hart {
	namespace Graphics {
		IndexBuffer::IndexBuffer(const uint32_t* data, int32_t count)
			: m_Count(count) {
			glGenBuffers(1, &m_BufferID);

			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), static_cast<const void*>(data), GL_STATIC_DRAW);
			unbind();
		}

		IndexBuffer::~IndexBuffer() {
			glDeleteBuffers(1, &m_BufferID);
		}

		void IndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}

		void IndexBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}