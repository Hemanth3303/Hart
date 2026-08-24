#include "HartPch.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Core/Assert.hpp"

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

		HART_DEBUG_ASSERT(!(vertexBuffer->getLayout().isEmpty()), "Attempting to add a VertexBuffer with an empty layout to VertexArray");
		if (vertexBuffer->getLayout().isEmpty()) {
			HART_ENGINE_INFO("Attempting to add a VertexBuffer with an empty layout to VertexArray, skipping.");
			return;
		}
		vertexBuffer->bind();
		uint32_t index = 0;
		for (const auto& element : vertexBuffer->getLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.getComponentCount(),
				element.getOpenGLType(),
				element.normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->getLayout().getStride(),
				reinterpret_cast<const void*>(element.offset));
			index++;
		}
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
