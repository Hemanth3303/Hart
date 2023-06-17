#include "HartPch.hpp"
#include "Renderer2D.hpp"

namespace Hart {
	namespace Graphics {

		std::unique_ptr<SceneData> Renderer2D::s_SceneData = std::make_unique<SceneData>();

		void Renderer2D::BeginScene(OrthographicCamera& camera) {
			s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
		}

		void Renderer2D::EndScene() {
			//TODO
		}

		void Renderer2D::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader) {
			HART_ASSERT_NOT_EQUAL(vertexArray->getIndexBuffer(), nullptr);

			shader->bind();
			shader->setUniform("uViewProjectionMatrix", s_SceneData->viewProjectionMatrix);

			vertexArray->bind();
			vertexArray->getIndexBuffer()->bind();

			RenderCommand::DrawIndexed(vertexArray);

			vertexArray->getIndexBuffer()->unbind();
			vertexArray->unbind();

			shader->unbind();
		}
	}
}