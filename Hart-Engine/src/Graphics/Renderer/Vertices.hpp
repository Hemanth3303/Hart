#pragma once

#include "Maths/Vec4.hpp"

namespace Hart {
	struct QuadVertex {
	public:
		Vec4 position;
		Vec4 color;
		Vec2 textureCoords;
		float textureIndex = -1.0f; //invalid texture slot
		float tilingFactor = 1.0f;
	};

	struct LineVertex {
		Vec4 position;
		Vec4 color;
	};

	struct TextVertex {
	public:
		Vec4 position;
		Vec4 color;
		Vec2 textureCoords;
	};
}