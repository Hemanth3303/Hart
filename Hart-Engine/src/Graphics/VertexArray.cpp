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

		void VertexArray::setVertexData(uint32_t index, int32_t sizeOfBuffer, int32_t noOfElementsPerVertex, float* dataBuffer, uint32_t strideToAttributeInBuffer, const void* pointer, GLenum dataType, GLboolean isNormalized, GLenum usage) {
			glBufferData(GL_ARRAY_BUFFER, sizeOfBuffer, static_cast<const void*>(dataBuffer), usage);
			glVertexAttribPointer(index, noOfElementsPerVertex, dataType, isNormalized, strideToAttributeInBuffer, pointer);
			glEnableVertexAttribArray(index);
		}

		void VertexArray::setIndexData(uint32_t noOfIndices, uint32_t* indexData) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, noOfIndices*sizeof(uint32_t), indexData, GL_STATIC_DRAW);
		}
	}
}