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

		void VertexArray::setVertexData(uint32_t index, uint32_t noOfElementsPerVertex, uint32_t noOfElements, float* vertexData) {
			glBufferData(GL_ARRAY_BUFFER, noOfElements * sizeof(float), vertexData, GL_STATIC_DRAW);
			glVertexAttribPointer(index, noOfElementsPerVertex, GL_FLOAT, GL_FALSE, noOfElementsPerVertex * sizeof(float), static_cast<const void*>(0));
			glEnableVertexAttribArray(index);
		}

		void VertexArray::setIndexData(uint32_t noOfIndices, uint32_t* indexData) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, noOfIndices*sizeof(uint32_t), indexData, GL_STATIC_DRAW);
		}
	}
}