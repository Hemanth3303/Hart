#include "HartPch.hpp"
#include "VertexArray.hpp"

namespace Hart {
	namespace Graphics {
		VertexArray::VertexArray() {
			glGenVertexArrays(1, &m_ArrayId);
		}

		VertexArray::~VertexArray() {
			glDeleteVertexArrays(1, &m_ArrayId);

		}

		void VertexArray::addBuffer(const std::unique_ptr<Buffer>& buffer, GLuint index) {
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, (const void*)0);

			buffer->unbind();
			unbind();
		}

		void VertexArray::bind() {
			glBindVertexArray(m_ArrayId);

        }

        void VertexArray::unbind() {
			glBindVertexArray(0);

        }

    }
}