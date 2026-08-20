#include "HartPch.hpp"
#include "Renderer3D.hpp"
#include "Renderer3DData.hpp"
#include "Graphics/OpenGLRenderer/OpenGLRenderer.hpp"
#include "Utils/Logger.hpp"

namespace Hart {
	static std::unique_ptr<Renderer3DData> s_Data = std::make_unique<Renderer3DData>();

	void Renderer3D::Init() {
		HART_ENGINE_INFO("Initializing Renderer3D");
	}

	void Renderer3D::DeInit() {
		HART_ENGINE_INFO("DeInitializing Renderer3D");
	}

	void Renderer3D::BeginScene(PerspectiveCamera& camera) {
		s_Data->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer3D::EndScene() {
		// TODO
	}

	void Renderer3D::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const Mat4& transformationMatrix) {

		shader->bind();
		shader->setUniform("uViewProjectionMatrix3D", s_Data->viewProjectionMatrix);
		shader->setUniform("uModelMatrix", transformationMatrix);

		OpenGLRenderer::DrawArrays(vertexArray);

		shader->unbind();
	}
}
