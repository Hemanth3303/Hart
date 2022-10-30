#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class IndexBuffer {
		public:
			// data: the usigned int array
			// count: the number of elements in the unsigned int array, ie, the number of indices in the unsigned int array
			IndexBuffer(const uint32_t* data, int32_t count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline const uint32_t& getBufferID() const { return m_BufferID; }
			inline const uint32_t& getCount() const { return m_Count; }

		private:
			uint32_t m_BufferID = 0;
			int32_t m_Count = 0;
		};
	}
}