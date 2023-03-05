#include "HartPch.hpp"
#include "Layer.hpp"


namespace Hart {
	namespace Graphics {
		Layer::Layer(Renderer2D* renderer, const Shader& shader, const Maths::Mat4& projectionMatrix)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix) {
			m_Shader.bind();
			m_Shader.setUniform("projection", m_ProjectionMatrix);
			m_Shader.unbind();
		}

		Layer::~Layer() {

		}

		void Layer::add(const Renderable2D* renderable) {
			m_Renderables.push_back(renderable);
		}

		void Layer::render() {
			m_Shader.bind();

			m_Renderer->begin();
			for (auto renderable : m_Renderables) {
				renderable->submit(m_Renderer);
			}
			m_Renderer->end();

			m_Renderer->flush();

			m_Shader.unbind();
		}
	}
}