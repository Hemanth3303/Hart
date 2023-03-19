#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class IndexBuffer {
		public:
			IndexBuffer(uint32_t* indices, uint32_t indexCount);
			~IndexBuffer();

			inline const uint32_t getIndexCount() const { return m_IndexCount; }

			void bind() const;
			void unbind() const;
		private:
			uint32_t m_ID;
			uint32_t m_IndexCount;
		};
	}
}