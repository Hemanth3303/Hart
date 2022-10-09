/*
* This class was made by following along with the cherno's sparky tutorial
*/

#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class IndexBuffer {
		public:
			// data the unsigned int array of indices
			// count is the number of elements in the array
			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_Count; }
		private:
			GLuint m_BufferId;
			GLuint m_Count;
		};
	}
}