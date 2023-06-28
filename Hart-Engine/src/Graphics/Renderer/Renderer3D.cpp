#include "HartPch.hpp"
#include "Renderer3D.hpp"

namespace Hart {
	namespace Graphics {

		std::unique_ptr<SceneData> Renderer3D::s_SceneData = std::make_unique<SceneData>();

		void Renderer3D::Init() {
			HART_ENGINE_LOG("Initializing Renderer3D");
			RenderCommand::Init();
		}

		void Renderer3D::DeInit() {
			HART_ENGINE_LOG("DeIntializing Renderer3D");
		}

		void Renderer3D::BeginScene(PerspectiveCamera& camera) {
			// s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
		}
		
		void Renderer3D::EndScene() {
			//TODO
		}

		void Renderer3D::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const Maths::Mat4& transformationMatrix) {
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