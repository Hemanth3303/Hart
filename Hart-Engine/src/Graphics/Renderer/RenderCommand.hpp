#pragma once

#include "HartPch.hpp"
#include "../VertexArray.hpp"

namespace Hart {
	class RenderCommand {
	public:
		static void Init();
		static void DeInit();

		// rgba values in range 0 to 1
		static void SetClearColor(const Vec4& color);
		static void Clear();
		static void SetViewPort(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height);
		static const std::int64_t GetMaxTextureSlotsPerShader();
		static const std::int64_t GetMaxTextureSlotsTotal();
		static void EnableDepthTest();
		static void DisableDepthTest();
		static void EnableBlending();
		static void DisableBlending();
		static void EnableWireFrameMode();
		static void DisableWireFrameMode();
		static void SetPixelPackAlignment(std::int32_t alignmentNumber);
		static void SetPixelUnpackAlignment(std::int32_t alignmentNumber);

		static void DrawLines(const std::shared_ptr<VertexArray>& vertexArray, std::uint32_t vertexCount);

		// by default uses vertex count of vertex array
		// if provided with a vertexCount greater than 0, it uses that vertexCount instead
		static void DrawArrays(const std::shared_ptr<VertexArray>& vertexArray, std::uint32_t vertexCount = 0);
		// by default uses index count of index buffer in vertex array
		// if provided with an indexCount greater than 0, it uses that indexCount instead
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, std::uint32_t indexCount = 0);
	};
}