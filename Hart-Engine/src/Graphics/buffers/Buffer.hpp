/*
* This class was made by following along with the cherno's sparky tutorial
*/

#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class Buffer {
		public:
			// data is a float array of vertices
			// count is the number of elements in the array
			// componentCount is the number of components per vertex in the array
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const { return m_ComponentCount; }
		private:
			GLuint m_BufferId = 0;
			GLuint m_ComponentCount;
		};
	}
}