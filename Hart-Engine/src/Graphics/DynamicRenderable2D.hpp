#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		class DynamicRenderable2D : public Renderable2D {
		public:
			DynamicRenderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color);
			~DynamicRenderable2D();
		};
	}
}