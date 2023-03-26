#include "HartPch.hpp"
#include "Renderer2D.hpp"

namespace Hart {
	namespace Graphics {
		void Renderer2D::BeginScene() {
			//TODO
		}

		void Renderer2D::EndScene() {
			//TODO
		}

		void Renderer2D::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
			vertexArray->bind();
			vertexArray->getIndexBuffer()->bind();

			RenderCommand::DrawIndexed(vertexArray);

			vertexArray->getIndexBuffer()->unbind();
			vertexArray->unbind();
		}
	}
}