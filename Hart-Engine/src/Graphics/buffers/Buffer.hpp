#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class Buffer {
		public:
			// data: the float array
			// count: the number of floats in the array
			// componentCount: the number of floats per vertex
			Buffer(const float* data, size_t count, int32_t componentCount);
			~Buffer();

			void bind() const;
			void unbind() const;

			inline const uint32_t& getBufferID() const { return m_BufferID; }
			inline const int32_t& getComponentCount() const { return m_ComponentCount; }

		private:
			uint32_t m_BufferID = 0;
			int32_t m_ComponentCount = 0;
		};
	}
}