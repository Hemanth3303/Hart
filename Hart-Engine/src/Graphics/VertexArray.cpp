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

		void VertexArray::setVertexData(uint32_t index, int32_t sizeOfBuffer, int32_t noOfElementsPerVertexAttribute, void* dataBuffer, uint32_t sizeOfOneVertexData, const void* offsetOfVertexAttribute, GLenum dataType, GLboolean isNormalized, GLenum usage) {
			glBufferData(GL_ARRAY_BUFFER, sizeOfBuffer, dataBuffer, usage);
			glVertexAttribPointer(index, noOfElementsPerVertexAttribute, dataType, isNormalized, sizeOfOneVertexData, offsetOfVertexAttribute);
			glEnableVertexAttribArray(index);
		}

		void VertexArray::setIndexData(uint32_t noOfIndices, uint32_t* indexData, GLenum usage) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, noOfIndices*sizeof(uint32_t), indexData, usage);
		}
	}
}