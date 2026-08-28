#include "HartPch.hpp"
#include "OpenGLRenderer.hpp"
#include "Core/Assert.hpp"
#include "Utils/Logger.hpp"

#include "glad/glad.h"

namespace Hart {
	RenderClearFlags operator|(RenderClearFlags lhs, RenderClearFlags rhs) {
		return static_cast<RenderClearFlags>(
			static_cast<GLbitfield>(lhs) | static_cast<GLbitfield>(rhs));
	}

	void OpenGLRenderer::Init() {
		HART_ENGINE_INFO(LogSource::EngineGraphics, "Initializing OpenGL Renderer");
		// collect data
		glGetInteger64v(GL_MAX_TEXTURE_IMAGE_UNITS, &s_Data.maxTextureSlotsPerShader);
		glGetInteger64v(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &s_Data.maxTextureSlotsCombined);

		s_Data.openglInfo.vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		s_Data.openglInfo.renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		s_Data.openglInfo.version = reinterpret_cast<const char*>(glGetString(GL_VERSION));

		// setup stuff
		EnableDepthTest();
		EnableBlending();
		EnableFaceCulling();
		SetCullFace(RenderCullFace::Back);
		SetWindingOrder(RenderWindingOrder::Clockwise);
		SetPixelPackAlignment(s_Data.pixelPackAlignment);
		SetPixelUnpackAlignment(s_Data.pixelUnpackAlignment);

		LogInfo();
	}

	void OpenGLRenderer::DeInit() {
		HART_ENGINE_INFO(LogSource::EngineGraphics, "DeInitializing OpenGL Renderer");
	}

	int64_t OpenGLRenderer::GetMaxTextureSlotsPerShader() {
		return s_Data.maxTextureSlotsPerShader;
	}

	int64_t OpenGLRenderer::GetMaxTextureSlotsTotal() {
		return s_Data.maxTextureSlotsCombined;
	}

	const OpenGLRendererData& OpenGLRenderer::GetOpenGLRendererData() {
		return s_Data;
	}

	void OpenGLRenderer::EnableDepthTest() {
		HART_ENGINE_TRACE(LogSource::EngineGraphics, "Enabled depth testing");
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRenderer::DisableDepthTest() {
		HART_ENGINE_TRACE(LogSource::EngineGraphics, "Disabled depth testing");
		glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRenderer::EnableBlending() {
		HART_ENGINE_TRACE(LogSource::EngineGraphics,
			"Enabled blending with ",
			"source_factor={GL_SRC_ALPHA} ",
			"and destination_factor={GL_ONE_MINUS_SRC_ALPHA}");
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderer::DisableBlending() {
		HART_ENGINE_TRACE(LogSource::EngineGraphics, "Disabled blending");
		glDisable(GL_BLEND);
	}

	void OpenGLRenderer::EnableWireFrameMode() {
		HART_ENGINE_TRACE(LogSource::EngineGraphics, "Enabled wireframe mode");
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void OpenGLRenderer::DisableWireFrameMode() {
		HART_ENGINE_TRACE(LogSource::EngineGraphics, "Disabled wireframe mode");
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OpenGLRenderer::EnableFaceCulling() {
		HART_ENGINE_TRACE(LogSource::EngineGraphics, "Enabled face culling");
		glEnable(GL_CULL_FACE);
	}

	void OpenGLRenderer::DisableFaceCulling() {
		HART_ENGINE_TRACE(LogSource::EngineGraphics, "Disabled face culling");
		glDisable(GL_CULL_FACE);
	}

	void OpenGLRenderer::SetClearColor(const Vec4& color) {
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void OpenGLRenderer::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height) {
		glViewport(x, y, width, height);
	}

	void OpenGLRenderer::SetPixelPackAlignment(int32_t alignmentNumber) {
		s_Data.pixelPackAlignment = alignmentNumber;
		glPixelStorei(GL_PACK_ALIGNMENT, s_Data.pixelPackAlignment);
	}

	void OpenGLRenderer::SetPixelUnpackAlignment(int32_t alignmentNumber) {
		s_Data.pixelUnpackAlignment = alignmentNumber;
		glPixelStorei(GL_UNPACK_ALIGNMENT, s_Data.pixelUnpackAlignment);
	}

	void OpenGLRenderer::SetCullFace(RenderCullFace cullFace) {
		glCullFace(static_cast<GLenum>(cullFace));
	}

	void OpenGLRenderer::SetWindingOrder(RenderWindingOrder windingOrder) {
		glFrontFace(static_cast<GLenum>(windingOrder));
	}

	void OpenGLRenderer::ClearFrameBuffer(RenderClearFlags clearFlag) {
		glClear(static_cast<GLbitfield>(clearFlag));
	}

	void OpenGLRenderer::DrawArrays(const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount) {
		HART_DEBUG_ASSERT((vertexArray != nullptr), "Reason: VertexArray is null");

		vertexArray->bind();
		uint32_t count = (vertexCount == 0 ? vertexArray->getVertexBuffer()->getVertexCount() : vertexCount);
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void OpenGLRenderer::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount) {
		HART_DEBUG_ASSERT((vertexArray != nullptr), "Reason: VertexArray is null");
		HART_DEBUG_ASSERT((vertexArray->getIndexBuffer() != nullptr), "Reason: IndexBuffer is null");

		vertexArray->bind();
		vertexArray->getIndexBuffer()->bind();
		uint32_t count = (indexCount == 0 ? vertexArray->getIndexBuffer()->getIndexCount() : indexCount);

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderer::LogInfo() {
		HART_ENGINE_INFO(
			LogSource::EngineGraphics,
			"\n\t\t\t==========================OpenGL Renderer Info==========================",
			"\n\t\t\t\tOpenGL Vendor: ", s_Data.openglInfo.vendor,
			"\n\t\t\t\tOpenGL Renderer: ", s_Data.openglInfo.renderer,
			"\n\t\t\t\tOpenGL Version: ", s_Data.openglInfo.version,
			"\n\t\t\t\tOpenGL Features:",
			"\n\t\t\t\t\tMax texture slots per shader: ", s_Data.maxTextureSlotsPerShader,
			"\n\t\t\t\t\tMax texture slots combined: ", s_Data.maxTextureSlotsCombined,
			"\n\t\t\t\t\tInitial pixel pack alignment: ", s_Data.pixelPackAlignment,
			"\n\t\t\t\t\tInitial pixel unpack alignment: ", s_Data.pixelUnpackAlignment,
			"\n\t\t\t=======================================================================");
	}
}
