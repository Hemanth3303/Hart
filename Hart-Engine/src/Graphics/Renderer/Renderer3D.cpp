#include "HartPch.hpp"
#include "Renderer3D.hpp"
#include "Renderer3DData.hpp"
#include "Renderer2D.hpp"
#include "RenderCommand.hpp"

namespace Hart {
	static std::unique_ptr<Renderer3DData> s_Data = std::make_unique<Renderer3DData>();

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
		 s_Data->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer3D::EndScene() {
		//TODO
	}

	void Renderer3D::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const Mat4& transformationMatrix) {

		shader->bind();
		shader->setUniform("uViewProjectionMatrix3D", s_Data->viewProjectionMatrix);
		shader->setUniform("uModelMatrix", transformationMatrix);

		RenderCommand::DrawArrays(vertexArray);

		shader->unbind();
	}
}