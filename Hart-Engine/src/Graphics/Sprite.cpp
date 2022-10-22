#include "HartPch.hpp"
#include "Sprite.hpp"

namespace Hart {
	namespace Graphics {
		Sprite::Sprite(float x, float y, float width, float height, const Maths::Vec4& color) 
			: Renderable2D(Maths::Vec3(x, y, 0.0f), Maths::Vec2(width, height), color) {

		}

		Sprite::Sprite(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color) 
			: Renderable2D(position, size, color) {

		}
	}
}