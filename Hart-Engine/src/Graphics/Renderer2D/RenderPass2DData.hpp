#pragma once

#include "Graphics/OpenGL/FrameBuffer.hpp"
#include "Graphics/Camera/OrthographicCamera.hpp"
#include "Maths/Vec4.hpp"
#include "Graphics/Colors.hpp"

#include <memory>

namespace Hart {
	struct RenderPass2DData {
		std::shared_ptr<FrameBuffer> fbo = nullptr;
		std::shared_ptr<OrthographicCamera> camera = nullptr;
		const Vec4& clearColor;
	};
}
