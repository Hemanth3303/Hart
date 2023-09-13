#pragma once

#include "HartPch.hpp"
#include "Shader.hpp"

#include "glad/glad.h"

namespace Hart {
	// A struct representing one attribute in a VertexBuffer
	struct BufferElement {
	public:
		ShaderDataType type;
		std::string name;
		std::uint32_t size;
		// offset of element in one vertex
		uint64_t offset;
		bool normalized;
	public:
		BufferElement(ShaderDataType ptype, const std::string& pname, bool pnormalized = false);
		std::uint32_t getComponentCount() const;
		GLenum getOpenGLType() const;
	};

	// A class representing the layout of attributes in a VertexBuffer.
	// Made up of BufferElements
	class BufferLayout {
	public:
		BufferLayout();
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		inline std::uint32_t getStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& getElements() const { return m_Elements; }
		inline bool isEmpty() const { return m_Elements.empty(); }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void calculateOffsetAndStride();
	private:
		std::vector<BufferElement> m_Elements;
		// stride of entire vertex
		std::uint32_t m_Stride = 0;
	};

	// A class representing an OpenGL VertexBuffer 
	class VertexBuffer {
	public:
		VertexBuffer(std::uint32_t size);
		VertexBuffer(float* vertices, std::uint32_t size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;
		void setData(const void* data, std::uint32_t size, std::uint32_t offset = 0);

		inline const BufferLayout& getLayout() const { return m_Layout; }
		// returns size in bytes of buffer passed in
		inline const std::uint32_t getSize() const { return m_Size; }
		inline const std::uint32_t getVertexCount() const { return m_Size; }
		// returns how many bytes one item in buffer is
		// note: since this class only accepts float* as buffers, this function returns the size of one float
		inline const std::uint32_t getSizeOfOneItemInBuffer() const { return static_cast<std::uint32_t>(sizeof(float)); }
		// returns how many items in the buffer, as in how many array values, not how many vertexAttributes
		// this function basically returns getSize() / getSizeOfOneItemInBuffer()
		inline const std::uint32_t getNumberOfItems() const { return getSize() / getSizeOfOneItemInBuffer(); }
		void setLayout(const BufferLayout& layout);
	private:
		std::uint32_t m_ID = 0;
		std::uint32_t m_Size;
		std::uint32_t m_VertexCount = 0;
		BufferLayout m_Layout;
	};
}