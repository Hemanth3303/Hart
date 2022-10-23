#include "HartPch.hpp"
#include "Layer.hpp"

namespace Hart {
	namespace Graphics {
		Layer::Layer(std::shared_ptr<Renderer2D> renderer, std::shared_ptr<Shader> shader, const Maths::Mat4& projectionMatrix)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix) {

		}

		Layer::~Layer() {

		}

		void Layer::add(std::shared_ptr<Renderable2D> renderable2d) {
			m_Renderables.push_back(renderable2d);
		}

		void Layer::render() {
			m_Shader->bind();

			m_Renderer->begin();
			for (const auto& renderable2d : m_Renderables) {
				m_Renderer->submit(renderable2d.get());
			}
			m_Renderer->end();
			m_Renderer->flush();

			m_Shader->unbind();
		}

	}
}