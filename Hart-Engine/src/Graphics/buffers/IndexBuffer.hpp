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
			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_Count; }
		private:
			GLuint m_ID;
			GLuint m_Count;
		};
	}
}