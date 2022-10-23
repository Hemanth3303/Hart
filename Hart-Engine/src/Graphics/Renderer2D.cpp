#include "HartPch.hpp"
#include "Renderer2D.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		Renderer2D::Renderer2D() {
			m_TransformationStack.push_back(Maths::Mat4::identity());
			m_TransformationBack = &m_TransformationStack.back();
		}

		void Renderer2D::push(const Maths::Mat4& matrix, bool override) {
			if (override) {
				m_TransformationStack.push_back(matrix);
			}
			else {
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
			}
			m_TransformationBack = &m_TransformationStack.back();
		}

		void Renderer2D::pop() {
			if (m_TransformationStack.size() > 1) {
				m_TransformationStack.pop_back();
			}
			m_TransformationBack = &m_TransformationStack.back();
		}
	}
}