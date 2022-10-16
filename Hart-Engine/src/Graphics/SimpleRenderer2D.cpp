#include "HartPch.hpp"
#include "SimpleRenderer2D.hpp"

namespace Hart {
	namespace Graphics {
		void SimpleRenderer2D::submit(const Renderable2D* renderable2d) {
			m_RenderQueue.push_back(renderable2d);
		}

		void SimpleRenderer2D::flush() {
			while (!m_RenderQueue.empty()) {
				const Renderable2D* renderable2d = m_RenderQueue.front();

				renderable2d->getShader().bind();
				renderable2d->getVAO()->bind();
				renderable2d->getIBO()->bind();

				renderable2d->getShader().setUniform("ml_matrix", Maths::Mat4::translate(renderable2d->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable2d->getIBO()->getCount(), GL_UNSIGNED_INT, nullptr);

				renderable2d->getVAO()->unbind();
				renderable2d->getIBO()->unbind();
				renderable2d->getShader().unbind();

				m_RenderQueue.pop_front();
			}
		}
	}
}