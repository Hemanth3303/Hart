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
			void setVertexData(uint32_t index, uint32_t noOfElementsPerVertex, uint32_t noOfElements, float* vertexData);
			void setIndexData(uint32_t noOfIndices, uint32_t* indexData);
		private:
			uint32_t m_ID;
		};
	}
}