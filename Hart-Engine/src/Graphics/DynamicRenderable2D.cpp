#include "HartPch.hpp"
#include "DynamicRenderable2D.hpp"

namespace Hart {
	namespace Graphics {
		Hart::Graphics::DynamicRenderable2D::DynamicRenderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color)
			:Renderable2D(position, size, color) {

		}

		DynamicRenderable2D::~DynamicRenderable2D() {

		}
	}
}