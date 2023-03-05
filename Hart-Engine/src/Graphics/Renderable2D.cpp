#include "HartPch.hpp"
#include "Renderable2D.hpp"
#include "Renderer2D.hpp"

namespace Hart {
	namespace Graphics {
        Renderable2D::Renderable2D() {

        }

        Renderable2D::Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color)
			: m_Position(position), m_Size(size), m_Color(color) {

		}

		Renderable2D::Renderable2D(float x, float y, float width, float height, const Maths::Vec4& color) 
			: m_Position(Maths::Vec3(x, y, 0.0f)), m_Size(Maths::Vec2(width, height)), m_Color(color) {

		}

		Renderable2D::~Renderable2D() {

		}
        
		void Renderable2D::submit(Renderer2D* render) const {
			render->submit(this);
        }
	}
}