#include "HartPch.hpp"
#include "Buffer.hpp"

namespace Hart {
	namespace Graphics {
		Buffer::Buffer(const float* data, size_t count, int32_t componentCount)
			: m_ComponentCount(componentCount) {
			glGenBuffers(1, &m_BufferID);
			
			bind();
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), static_cast<const void*>(data), GL_STATIC_DRAW);
			unbind();
		}

		Buffer::~Buffer() {
			glDeleteBuffers(1, &m_BufferID);
		}

		void Buffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		}

		void Buffer::unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}