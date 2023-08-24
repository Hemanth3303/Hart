#pragma once

#include "HartPch.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include "glad/glad.h"

namespace Hart {
	// Class representing an OpenGL VertexArray
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;

		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		inline const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return m_vertexBuffers; }
		inline const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return m_IndexBuffer; }

	private:
		std::uint32_t m_ID;
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}