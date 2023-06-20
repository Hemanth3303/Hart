#include "HartPch.hpp"
#include "Renderer.hpp"

namespace Hart {
	namespace Graphics {

		std::unique_ptr<SceneData> Renderer::s_SceneData = std::make_unique<SceneData>();

		void Renderer::Init() {
			HART_ENGINE_LOG("Initializing Renderer");
			RenderCommand::Init();
		}

		void Renderer::DeInit() {
			HART_ENGINE_LOG("DeIntializing Renderer");
		}

		void Renderer::BeginScene(OrthographicCamera& camera) {
			s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
		}
		
		void Renderer::EndScene() {
			//TODO
		}

		void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const Maths::Mat4& transformationMatrix) {
			HART_ASSERT_NOT_EQUAL(vertexArray->getIndexBuffer(), nullptr);

			shader->bind();
			shader->setUniform("uViewProjectionMatrix", s_SceneData->viewProjectionMatrix);
			shader->setUniform("uModelMatrix", transformationMatrix);

			vertexArray->bind();
			vertexArray->getIndexBuffer()->bind();

			RenderCommand::DrawIndexed(vertexArray);

			vertexArray->getIndexBuffer()->unbind();
			vertexArray->unbind();

			shader->unbind();
		}
	}
}