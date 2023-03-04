#include "HartPch.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

namespace Hart {
	namespace Graphics {
		Hart::Graphics::VertexArray::VertexArray() {
			glGenVertexArrays(1, &m_ID);
		}

		VertexArray::~VertexArray() {
			glDeleteVertexArrays(1, &m_ID);
		}

		void VertexArray::bind() const {
			glBindVertexArray(m_ID);
		}

		void VertexArray::unbind() const {
			glBindVertexArray(0);
		}

		void VertexArray::setVertexData(uint32_t index, uint32_t noOfElementsPerVertex, uint32_t sizeOfBuffer, uint32_t stride, float* vertexData, GLenum mode, const void* offset) {
			glBufferData(GL_ARRAY_BUFFER, sizeOfBuffer, vertexData, mode);
			glVertexAttribPointer(index, noOfElementsPerVertex, GL_FLOAT, GL_FALSE, stride, offset);
			glEnableVertexAttribArray(index);
		}

		void VertexArray::setIndexData(uint32_t noOfIndices, uint32_t* indexData, GLenum mode) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, noOfIndices*sizeof(uint32_t), indexData, mode);
		}
	}
}