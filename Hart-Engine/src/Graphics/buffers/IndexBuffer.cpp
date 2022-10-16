#include "HartPch.hpp"
#include "IndexBuffer.hpp"

namespace Hart {
	namespace Graphics {
		IndexBuffer::IndexBuffer(GLuint* data, GLsizei count)
			: m_Count(count) {
			glGenBuffers(1, &m_IndexBufferId);
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			unbind();
		}

		IndexBuffer::~IndexBuffer() {
			glDeleteBuffers(1, &m_IndexBufferId);
		}

		void IndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
		}

		void IndexBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}