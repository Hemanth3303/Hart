#include "HartPch.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

namespace Hart {
	VertexArray::VertexArray() {
		glCreateVertexArrays(1, &m_ID);
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

	void VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		glBindVertexArray(m_ID);

		HART_ASSERT_NOT_EQUAL(vertexBuffer->getLayout().isEmpty(), true, "Attempting to add a VertexBuffer with an empty layout to VertexArray");
		vertexBuffer->bind();
		std::uint32_t index = 0;
		std::uint32_t itemsPerVertex = 0;
		for (const auto& element : vertexBuffer->getLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.getComponentCount(),
				element.getOpenGLType(),
				element.normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->getLayout().getStride(),
				reinterpret_cast<const void*>(element.offset)
			);
			index++;
			itemsPerVertex += element.getComponentCount();
		}
		std::uint32_t numberOfVerticesVertexBuffer = vertexBuffer->getNumberOfItems() / itemsPerVertex;
		m_VertexCount += numberOfVerticesVertexBuffer;

		vertexBuffer->unbind();
		m_vertexBuffer = vertexBuffer;

		glBindVertexArray(0);
	}

	void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_ID);

		indexBuffer->bind();
		m_IndexBuffer = indexBuffer;
		indexBuffer->unbind();
	}
}