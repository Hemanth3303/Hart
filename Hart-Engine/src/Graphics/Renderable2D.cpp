#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		Renderable2D::Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color)
			:m_VertexData(position, size, color) {

		}

		Renderable2D::~Renderable2D() {

		}
	}
}