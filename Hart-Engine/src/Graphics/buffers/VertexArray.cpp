#include "HartPch.hpp"
#include "VertexArray.hpp"

namespace Hart {
	namespace Graphics {
		VertexArray::VertexArray() {
			glGenVertexArrays(1, &m_ID);
		}

        VertexArray::~VertexArray() {

			for (size_t i = 0, n = m_Buffers.size(); i < n; i++) {
				delete m_Buffers[i];
			}
			glDeleteVertexArrays(1, &m_ID);

        }

		void VertexArray::addBuffer(Buffer* buffer, GLuint index) {
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, (const void*)0);

			buffer->unbind();
			unbind();
		}

        void VertexArray::bind() {
			glBindVertexArray(m_ID);

        }

        void VertexArray::unbind() {
			glBindVertexArray(0);

        }

    }
}