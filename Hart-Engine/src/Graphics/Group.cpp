#include "HartPch.hpp"
#include "Group.hpp"
#include "Renderer2D.hpp"

namespace Hart {
	namespace Graphics {
		Group::Group(const Maths::Mat4& transformationMatrix) 
			: m_TransformationMatrix(transformationMatrix) {

		}

		Group::~Group() {

		}

		void Group::add(Renderable2D* renderable) {
			m_Renderables.push_back(renderable);
		}
		void Group::submit(Renderer2D* renderer) const {
			renderer->pushTransformationMatrix(m_TransformationMatrix);
			for (const Renderable2D* renderable : m_Renderables) {
				renderable->submit(renderer);
			}
			renderer->popTransformationMatrix();
		}
	}
}