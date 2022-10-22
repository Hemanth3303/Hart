#include "HartPch.hpp"
#include "VertexArray.hpp"

namespace Hart {
	namespace Graphics {
        VertexArray::VertexArray() {
			glGenVertexArrays(1, &m_ArrayId);
        }

        VertexArray::~VertexArray() {
			for (size_t i = 0; i < m_Buffers.size(); i++) {
				delete m_Buffers[i];
			}
			glDeleteVertexArrays(1, &m_ArrayId);
        }

        void VertexArray::addBuffer(Buffer* buffer, GLuint index) {
			m_Buffers.push_back(buffer);

			bind();
			buffer->bind();

			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, static_cast<const void*>(0));
			glEnableVertexAttribArray(index);

			buffer->unbind();
			unbind();
        }

        void VertexArray::bind() const {
			glBindVertexArray(m_ArrayId);
        }

        void VertexArray::unbind() const {
			glBindVertexArray(0);
        }
    }
}