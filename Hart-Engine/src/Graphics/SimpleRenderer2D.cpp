#include "HartPch.hpp"
#include "SimpleRenderer2D.hpp"

namespace Hart {
	namespace Graphics {
		void SimpleRenderer2D::submit(const Renderable2D* renderable2d) {
			m_RenderQueue.push_back(dynamic_cast<const StaticSprite*>(renderable2d));
		}

		void SimpleRenderer2D::flush() {
			while (!m_RenderQueue.empty()) {
				const StaticSprite* staticSprite = m_RenderQueue.front();

				staticSprite->getShader().bind();
				staticSprite->getVAO()->bind();
				staticSprite->getIBO()->bind();

				staticSprite->getShader().setUniform("ml_matrix", Maths::Mat4::translate(staticSprite->getPosition()));
				glDrawElements(GL_TRIANGLES, staticSprite->getIBO()->getCount(), GL_UNSIGNED_INT, nullptr);

				staticSprite->getVAO()->unbind();
				staticSprite->getIBO()->unbind();
				staticSprite->getShader().unbind();

				m_RenderQueue.pop_front();
			}
		}
	}
}