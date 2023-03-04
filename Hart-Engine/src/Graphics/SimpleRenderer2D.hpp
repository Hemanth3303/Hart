/*
* A simple 2d renderer that draws one StaticRenderable2D at a time
*/

#pragma once

#include "HartPch.hpp"
#include "Renderer2D.hpp"
#include "StaticRenderable2D.hpp"

namespace Hart {
	namespace Graphics {
		class SimpleRenderer2D : public Renderer2D {
		public:
			virtual void submit(const Renderable2D* renderable) override;
			virtual void flush() override;
		};
	}
}