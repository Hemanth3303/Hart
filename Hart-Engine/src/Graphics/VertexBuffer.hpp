#pragma once

#include "HartPch.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class VertexBuffer {
		public:
			VertexBuffer();
			~VertexBuffer();

			void bind() const;
			void unbind() const;
		private:
			uint32_t m_ID;
		};
	}
}