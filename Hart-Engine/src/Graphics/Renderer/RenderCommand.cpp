#include "HartPch.hpp"
#include "RenderCommand.hpp"

namespace Hart {
	void RenderCommand::Init() {
		EnableDepthTest();
		EnableBlending();

		HART_ENGINE_LOG("Initializing OpenGL Renderer");
		HART_ENGINE_LOG(
			"OpenGL Renderer Info:",
			std::string("\t\t\t\t\tVendor: ") + reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
			std::string("\t\t\t\t\tRenderer: ") + reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
			std::string("\t\t\t\t\tVersion: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION))
		);
	}
	void RenderCommand::DeInit() {
		HART_ENGINE_LOG("DeInitializing OpenGL Renderer");
	}
	void RenderCommand::SetClearColor(const Vec4& color) {
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void RenderCommand::Clear() {
		// TODO: ask for flags to what to clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::SetViewPort(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
		glViewport(x, y, width, height);
	}

	void RenderCommand::SetLineWidth(float width) {
		glLineWidth(width);
	}

	const std::int64_t RenderCommand::GetMaxTextureSlotsPerShader() {
		std::int64_t maxNoOfTextureSlotsPerShader;
		glGetInteger64v(GL_MAX_TEXTURE_IMAGE_UNITS, &maxNoOfTextureSlotsPerShader);

		return maxNoOfTextureSlotsPerShader;
	}

	const std::int64_t RenderCommand::GetMaxTextureSlotsTotal() {
		return GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
	}

	void RenderCommand::EnableDepthTest() {
		glEnable(GL_DEPTH_TEST);
	}

	void RenderCommand::DisableDepthTest() {
		glDisable(GL_DEPTH_TEST);
	}

	void RenderCommand::EnableBlending() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderCommand::DisableBlending() {
		glDisable(GL_BLEND);
	}

	void RenderCommand::EnableWireFrameMode() {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void RenderCommand::DisableWireFrameMode() {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

    void RenderCommand::EnableSmoothLines() {
		glEnable(GL_LINE_SMOOTH);
	}

    void RenderCommand::DisableSmoothLines() {
		glDisable(GL_LINE_SMOOTH);
	}

	void RenderCommand::DrawLines(const std::shared_ptr<VertexArray>& vertexArray, std::uint32_t vertexCount) {
		HART_ASSERT_NOT_EQUAL(vertexArray, nullptr, "Reason: VertexArray is null");
		vertexArray->bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}

	void RenderCommand::DrawArrays(const std::shared_ptr<VertexArray>& vertexArray, std::uint32_t vertexCount) {
		HART_ASSERT_NOT_EQUAL(vertexArray, nullptr, "Reason: VertexArray is null");

		vertexArray->bind();
		std::uint32_t count = (vertexCount == 0 ? vertexArray->getVertexCount() : vertexCount);
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, std::uint32_t indexCount) {
		HART_ASSERT_NOT_EQUAL(vertexArray, nullptr, "Reason: VertexArray is null");
		HART_ASSERT_NOT_EQUAL(vertexArray->getIndexBuffer(), nullptr, "Reason: IndexBuffer is null");

		vertexArray->bind();
		vertexArray->getIndexBuffer()->bind();
		std::uint32_t count = (indexCount == 0 ? vertexArray->getIndexBuffer()->getIndexCount() : indexCount);

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}