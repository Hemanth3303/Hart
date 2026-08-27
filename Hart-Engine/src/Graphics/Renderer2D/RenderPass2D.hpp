#pragma once

#include "Graphics/OpenGL/FrameBuffer.hpp"
#include "Graphics/Camera/OrthographicCamera.hpp"
#include "Maths/Vec4.hpp"
#include "Graphics/Colors.hpp"

namespace Hart {
	struct RenderPass2D {
		const FrameBuffer& fbo;
		const OrthographicCamera& camera;
		const Vec4& clearColor = Hart::Black;
	};
}
