#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		// Class representing an OpenGL VertexBuffer 
		class IndexBuffer {
		public:
			IndexBuffer(std::uint32_t* indices, std::uint32_t indexCount);
			~IndexBuffer();

			inline const std::uint32_t getIndexCount() const { return m_IndexCount; }

			void bind() const;
			void unbind() const;
		private:
			std::uint32_t m_ID;
			std::uint32_t m_IndexCount;
		};
	}
}