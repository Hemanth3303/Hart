#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class IndexBuffer {
		public:
			IndexBuffer(GLuint* data, GLsizei count);
			IndexBuffer(const IndexBuffer&) = delete;
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline const GLuint& getCount() const { return m_Count; }

		private:
			GLuint m_IndexBufferId;
			GLuint m_Count;
		};
	}
}