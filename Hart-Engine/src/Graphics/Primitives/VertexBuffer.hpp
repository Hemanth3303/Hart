#pragma once

#include "HartPch.hpp"
#include "Shader.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		// A struct representing one attribute in a VertexBuffer
		struct BufferElement {
		public:
			ShaderDataType type;
			std::string name;
			uint32_t size;
			uint64_t offset;
			bool normalized;
		public:
			BufferElement(ShaderDataType ptype, const std::string& pname, bool pnormalized = false);
			uint32_t getComponentCount() const;
			GLenum getOpenGLType() const;
		};

		// A class representing the layout of attributes in a VertexBuffer.
		// Made up of BufferElements
		class BufferLayout {
		public:
			BufferLayout();
			BufferLayout(const std::initializer_list<BufferElement>& elements);
			
			inline uint32_t getStride() const { return m_Stride; }
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
			uint32_t m_Stride = 0;
		};

		// A class representing an OpenGL VertexBuffer 
		class VertexBuffer {
		public:
			VertexBuffer(float* vertices, uint32_t size);
			~VertexBuffer();

			inline const BufferLayout& getLayout() const { return m_Layout; }
			inline void setLayout(const BufferLayout& layout) { m_Layout = layout; }

			void bind() const;
			void unbind() const;
		private:
			uint32_t m_ID;
			BufferLayout m_Layout;
		};
	}
}