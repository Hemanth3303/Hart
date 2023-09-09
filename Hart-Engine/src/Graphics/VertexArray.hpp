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

		// Note: Only add a vertexbuffer after settings its layout
		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		inline const std::shared_ptr<VertexBuffer>& getVertexBuffers() const { return m_vertexBuffer; }
		inline const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return m_IndexBuffer; }
		inline const std::uint32_t getVertexCount() const {return m_VertexCount; }

	private:
		std::uint32_t m_ID = 0;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::uint32_t m_VertexCount = 0;
	};
}