#include "HartPch.hpp"
#include "IndexBuffer.hpp"

namespace Hart {
	namespace Graphics {
		IndexBuffer::IndexBuffer(uint32_t indexCount) 
			:m_IndexCount(indexCount) {
			glGenBuffers(1, &m_ID);
		}

		IndexBuffer::~IndexBuffer() {
			glDeleteBuffers(1, &m_ID);
		}

		void IndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		}

		void IndexBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}