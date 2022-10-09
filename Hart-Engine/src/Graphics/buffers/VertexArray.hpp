/*
* This class was made by following along with the cherno's sparky tutorial
*/

#pragma once

#include "HartPch.hpp"
#include "Buffer.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class VertexArray {
		public:
			VertexArray();
			~VertexArray();

			// buffer is the Hart::Graphics::Buffer object to be passed in
			// index is the layout location value used in the shader
			void addBuffer(Buffer* buffer, GLuint index);
			void bind();
			void unbind();
		private:
			GLuint m_ID = 0;
			std::vector<Buffer*> m_Buffers;
		};
	}
}