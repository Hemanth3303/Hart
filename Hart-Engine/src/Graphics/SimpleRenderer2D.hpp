/*
* Class used to draw StaticSprites one at a time
* Extremely inefficient, should only be used for testing purposes
*/

#pragma once

#include "HartPch.hpp"
#include "Renderer2D.hpp"
#include "StaticSprite.hpp"

namespace Hart {
	namespace Graphics {
		class SimpleRenderer2D : public Renderer2D {
		public:
			SimpleRenderer2D() = default;
			SimpleRenderer2D(const SimpleRenderer2D&) = delete;
			~SimpleRenderer2D() = default;

			void submit(const Renderable2D* renderable2d) override;
			void flush() override;
		private:
			std::deque<const StaticSprite*> m_RenderQueue;
		};
	}
}