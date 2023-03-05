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
			//default draw type is GL_STATIC_DRAW
			void setVertexData(uint32_t index, uint32_t noOfElementsPerVertex, uint32_t sizeOfBuffer, uint32_t stride, GLenum dataType = GL_FLOAT, GLboolean isNormalaized = GL_FALSE, float* vertexData = NULL, GLenum mode = GL_STATIC_DRAW, const void* offset = static_cast<const void*>(0));
			void setIndexData(uint32_t noOfIndices, uint32_t* indexData, GLenum mode = GL_STATIC_DRAW);
		private:
			uint32_t m_ID;
		};
	}
}