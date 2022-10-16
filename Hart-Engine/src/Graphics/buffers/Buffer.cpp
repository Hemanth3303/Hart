#include "HartPch.hpp"
#include "Buffer.hpp"

namespace Hart {
	namespace Graphics {
		Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount) 
			: m_ComponentCount(componentCount) {
			glGenBuffers(1, &m_BufferId);
			bind();
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			unbind();
		}

		Buffer::~Buffer() {
			glDeleteBuffers(1, &m_BufferId);
		}

		void Buffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
		}

		void Buffer::unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}