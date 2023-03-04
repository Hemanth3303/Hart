#include "HartPch.hpp"
#include "SimpleRenderer2D.hpp"

namespace Hart {
	namespace Graphics {
		void SimpleRenderer2D::submit(const Renderable2D* renderable) {
			m_RenderQueue.push_back(renderable);
		}

		void SimpleRenderer2D::flush() {
			while (!m_RenderQueue.empty()) {
				const Renderable2D* renderable = m_RenderQueue.front();

				renderable->getShader()->bind();
				renderable->getVertexArray()->bind();
				renderable->getIndexBuffer()->bind();
				
				glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, 0);
				
				renderable->getIndexBuffer()->unbind();
				renderable->getVertexArray()->unbind();
				renderable->getShader()->unbind();

				m_RenderQueue.pop_front();
			}
		}
	}
}