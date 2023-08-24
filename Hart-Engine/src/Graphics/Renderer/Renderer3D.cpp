#include "HartPch.hpp"
#include "Renderer3D.hpp"
#include "Renderer2D.hpp"
#include "RenderCommand.hpp"

namespace Hart {
	std::unique_ptr<Scene3DData> Renderer3D::s_SceneData = std::make_unique<Scene3DData>();

	void Renderer3D::Init() {
		RenderCommand::Init();
		Renderer2D::Init();
		HART_ENGINE_LOG("Initializing Renderer3D");
	}

	void Renderer3D::DeInit() {
		Renderer2D::DeInit();
		HART_ENGINE_LOG("DeIntializing Renderer3D");
		RenderCommand::DeInit();
	}

	void Renderer3D::BeginScene(PerspectiveCamera& camera) {
		// s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer3D::EndScene() {
		//TODO
	}

	void Renderer3D::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const Mat4& transformationMatrix) {
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