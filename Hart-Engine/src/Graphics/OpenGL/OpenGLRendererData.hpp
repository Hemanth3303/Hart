#pragma once

#include <cstdint>
#include <string>

namespace Hart {
	struct OpenGLInfo {
		std::string vendor;
		std::string renderer;
		std::string version;
	};

	struct OpenGLRendererData {
		int32_t pixelPackAlignment = 4;
		int32_t pixelUnpackAlignment = 4;
		int64_t maxTextureSlotsPerShader = 0;
		int64_t maxTextureSlotsCombined = 0;

		OpenGLInfo openglInfo;
	};
}
