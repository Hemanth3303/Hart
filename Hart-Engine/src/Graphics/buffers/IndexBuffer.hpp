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

			inline const GLuint& getComponentCount() const { return m_Count; }

		private:
			GLuint m_IndexBufferId;
			GLuint m_Count;
		};
	}
}