#include "HartPch.hpp"
#include "Group.hpp"

namespace Hart {
	namespace Graphics {
		Group::Group(const Maths::Mat4& transform) 
			: m_TransformationMatrix(transform) {

		}

		void Group::add(std::shared_ptr<Renderable2D> renderable2d) {
			m_Renderables.push_back(renderable2d);
		}

		void Group::submit(Renderer2D* renderer2d) const {
			renderer2d->push(m_TransformationMatrix);
			for (const std::shared_ptr<Renderable2D> renderable2d : m_Renderables) {
				renderable2d->submit(renderer2d);
			}
			renderer2d->pop();
		}

	}
}