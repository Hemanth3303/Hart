#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class VertexArray {
		public:
			VertexArray();
			~VertexArray();

			void bind() const;
			void unbind() const;
			void setVertexData(uint32_t index, int32_t sizeOfBuffer, int32_t noOfElementsPerVertex, float* dataBuffer, uint32_t strideToAttributeInBuffer = 0, GLenum dataType = GL_FLOAT, GLboolean isNormalized = GL_FALSE, GLenum usage = GL_STATIC_DRAW, const void* pointer = static_cast<const void*>(0));
			void setIndexData(uint32_t noOfIndices, uint32_t* indexData);
		private:
			uint32_t m_ID;
		};
	}
}