#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class Buffer {
		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			Buffer(const Buffer&) = delete;
			~Buffer();

			void bind() const;
			void unbind() const;

			inline const GLuint& getComponentCount() const { return m_ComponentCount; }

		private:
			GLuint m_BufferId;
			GLuint m_ComponentCount;
		};
	}
}