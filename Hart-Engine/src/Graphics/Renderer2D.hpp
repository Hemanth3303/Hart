/*
* abstract class for 2d renderers
*/

#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"
#include "Maths/Maths.hpp"

namespace Hart {
	namespace Graphics {
		class Renderer2D {
		public:
			virtual void begin() {}
			
			//adds to render queue
			virtual void submit(const Renderable2D* renderable2d) = 0;
			//draw the elements in the render queue
			virtual void flush() = 0;

			virtual void end() {}
		};
	}
}