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
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const { return m_ComponentCount; }
		private:
			GLuint m_ID = 0;
			GLuint m_ComponentCount;
		};
	}
}