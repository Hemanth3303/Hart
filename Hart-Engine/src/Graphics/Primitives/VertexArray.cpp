#include "HartPch.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

namespace Hart {
	namespace Graphics {
		Hart::Graphics::VertexArray::VertexArray() {
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
		// Adds a vertexbuffer to the vertexarray
		// Note: Only add a vertexbuffer after settings its layout
		void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
			glBindVertexArray(m_ID);

			HART_ASSERT_NOT_EQUAL(vertexBuffer->getLayout().isEmpty(), true);
			if (vertexBuffer->getLayout().isEmpty()) {
				HART_ENGINE_ERROR("Attempting to add a VertexBuffer with an empty layout to VertexArray, aborting attempt");
				return;
			}
			vertexBuffer->bind();
			std::uint32_t index = 0;
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
			}
			vertexBuffer->unbind();
			m_vertexBuffers.push_back(vertexBuffer);
			
			glBindVertexArray(0);
		}

		void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
			glBindVertexArray(m_ID);

			indexBuffer->bind();
			m_IndexBuffer = indexBuffer;
			indexBuffer->unbind();

			glBindVertexArray(0);
		}
	}
}