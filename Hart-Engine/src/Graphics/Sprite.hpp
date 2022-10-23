#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		class Sprite : public Renderable2D {
		public:
			Sprite(float x, float y, float width, float height, const Maths::Vec4& color);
			Sprite(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color);
		};
	}
}