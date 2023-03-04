#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		class Renderer2D {
		public:
			virtual void begin() {}
			
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;

			virtual void end() {}

		protected:
			std::deque<const Renderable2D*> m_RenderQueue;
		};
	}
}