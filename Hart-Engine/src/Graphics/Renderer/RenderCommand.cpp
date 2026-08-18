#include "HartPch.hpp"
#include "RenderCommand.hpp"
#include "Core/Assert.hpp"
#include "Utils/Logger.hpp"

#include "glad/glad.h"

namespace Hart {
	void RenderCommand::Init() {
		EnableDepthTest();
		EnableBlending();
		SetPixelPackAlignment(4);
		SetPixelUnpackAlignment(4);

		HART_ENGINE_LOG("Initializing OpenGL Renderer");
		HART_ENGINE_LOG(
			"\n\t\t\t=======================OpenGL Renderer Info=======================",
			"\n\t\t\t\tVendor: ", glGetString(GL_VENDOR),
			"\n\t\t\t\tRenderer: ", glGetString(GL_RENDERER),
			"\n\t\t\t\tVersion: ", glGetString(GL_VERSION),
			"\n\t\t\t==================================================================");
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

	void RenderCommand::SetViewPort(int32_t x, int32_t y, int32_t width, int32_t height) {
		glViewport(x, y, width, height);
	}

	const int64_t RenderCommand::GetMaxTextureSlotsPerShader() {
		int64_t maxNoOfTextureSlotsPerShader;
		glGetInteger64v(GL_MAX_TEXTURE_IMAGE_UNITS, &maxNoOfTextureSlotsPerShader);

		return maxNoOfTextureSlotsPerShader;
	}

	const int64_t RenderCommand::GetMaxTextureSlotsTotal() {
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

	void RenderCommand::SetPixelPackAlignment(int32_t alignmentNumber) {
		glPixelStorei(GL_PACK_ALIGNMENT, alignmentNumber);
	}

	void RenderCommand::SetPixelUnpackAlignment(int32_t alignmentNumber) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, alignmentNumber);
	}

	void RenderCommand::DrawLines(const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount) {
		HART_DEBUG_ASSERT((vertexArray != nullptr), "Reason: VertexArray is null");
		vertexArray->bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}

	void RenderCommand::DrawArrays(const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount) {
		HART_DEBUG_ASSERT((vertexArray != nullptr), "Reason: VertexArray is null");

		vertexArray->bind();
		uint32_t count = (vertexCount == 0 ? vertexArray->getVertexBuffer()->getVertexCount() : vertexCount);
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount) {
		HART_DEBUG_ASSERT((vertexArray != nullptr), "Reason: VertexArray is null");
		HART_DEBUG_ASSERT((vertexArray->getIndexBuffer() != nullptr), "Reason: IndexBuffer is null");

		vertexArray->bind();
		vertexArray->getIndexBuffer()->bind();
		uint32_t count = (indexCount == 0 ? vertexArray->getIndexBuffer()->getIndexCount() : indexCount);

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}
