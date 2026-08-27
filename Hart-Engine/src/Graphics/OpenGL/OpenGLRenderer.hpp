#pragma once

#include "VertexArray.hpp"
#include "OpenGLRendererData.hpp"

namespace Hart {
	enum class RenderClearFlags : GLbitfield {
		ColorBuffer = GL_COLOR_BUFFER_BIT,
		DepthBuffer = GL_DEPTH_BUFFER_BIT,
		StencilBuffer = GL_STENCIL_BUFFER_BIT,
	};

	enum class RenderCullFace : GLenum {
		Front = GL_FRONT,
		Back = GL_BACK,
		FrontAndBack = GL_FRONT_AND_BACK,
	};

	enum class RenderWindingOrder : GLenum {
		Clockwise = GL_CW,
		CounterClockwise = GL_CCW,
	};

	RenderClearFlags operator|(RenderClearFlags lhs, RenderClearFlags rhs);

	class OpenGLRenderer {
	public:
		static void Init();
		static void DeInit();

		// =====================enable/disable features===================== //

		static void EnableDepthTest();
		static void DisableDepthTest();
		static void EnableBlending();
		static void DisableBlending();
		static void EnableWireFrameMode();
		static void DisableWireFrameMode();
		static void EnableFaceCulling();
		static void DisableFaceCulling();

		// =====================getters===================== //

		static int64_t GetMaxTextureSlotsPerShader();
		static int64_t GetMaxTextureSlotsTotal();
		static const OpenGLRendererData& GetOpenGLRendererData();

		// =====================setters===================== //

		// rgba values in range 0 to 1
		static void SetClearColor(const Vec4& color);
		static void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);
		static void SetPixelPackAlignment(int32_t alignmentNumber);
		static void SetPixelUnpackAlignment(int32_t alignmentNumber);
		static void SetCullFace(RenderCullFace cullFace);
		static void SetWindingOrder(RenderWindingOrder windingOrder);

		// =====================drawing related===================== //

		// Bitwise OR the target values. eg: RenderClearFlags::ColorBuffer | RenderClearFlags::DepthBuffer
		static void ClearFrameBuffer(RenderClearFlags clearFlag);

		// by default uses vertex count of vertex array
		// if provided with a vertexCount greater than 0, it uses that vertexCount instead
		static void DrawArrays(const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount = 0);
		// by default uses index count of index buffer in vertex array
		// if provided with an indexCount greater than 0, it uses that indexCount instead
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0);

	private:
		static void LogInfo();

	private:
		inline static OpenGLRendererData s_Data{};
	};
}
