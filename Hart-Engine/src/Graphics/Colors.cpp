#include "HartPch.hpp"
#include "Colors.hpp"

namespace Hart {
	Vec4 NormalizeRGB255(const Vec4& color) {
		return {
			color.x / 255.0f,
			color.y / 255.0f,
			color.z / 255.0f,
			1.0f
		};
	}
	Vec4 NormalizeRGBA255(const Vec4& color) {
		return {
			color.x / 255.0f,
			color.y / 255.0f,
			color.z / 255.0f,
			color.w / 255.0f
		};
	}
}