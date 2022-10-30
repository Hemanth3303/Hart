#include "HartPch.hpp"
#include "VertexArray.hpp"

namespace Hart {
	namespace Graphics {
		VertexArray::VertexArray() {
			glGenVertexArrays(1, &m_ArrayID);
		}

		VertexArray::~VertexArray() {
			glDeleteVertexArrays(1, &m_ArrayID);
		}

		void VertexArray::bind() const {
			glBindVertexArray(m_ArrayID);
		}

		void VertexArray::unbind() const {
			glBindVertexArray(0);
		}

		void VertexArray::addBuffer(const Buffer& buffer, uint32_t index) {
			bind();
			buffer.bind();
			glVertexAttribPointer(index, buffer.getComponentCount(), GL_FLOAT, GL_FALSE, buffer.getComponentCount() * sizeof(float), static_cast<const void*>(0));
			glEnableVertexAttribArray(index);
			buffer.unbind();
			unbind();
		}
	}
}