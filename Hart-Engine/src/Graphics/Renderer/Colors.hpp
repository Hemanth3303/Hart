#pragma once

#include "HartPch.hpp"
#include "Maths/Vec4.hpp"

// TODO: Add more colors

namespace Hart {
	namespace Graphics {
		inline const Maths::Vec4 White = { 255.0f, 255.0f, 255.0f, 255.0f };
		inline const Maths::Vec4 Black = { 0.0f, 0.0f, 0.0f, 255.0f };
		inline const Maths::Vec4 Red = { 255.0f, 0.0f, 0.0f, 255.0f };
		inline const Maths::Vec4 Green = { 0.0f, 255.0f, 0.0f, 255.0f };
		inline const Maths::Vec4 Blue = { 0.0f, 0.0f, 255.0f, 255.0f };
		inline const Maths::Vec4 Yellow = { 255.0f, 255.0f, 0.0f, 255.0f };
		inline const Maths::Vec4 Cyan = { 0.0f, 255.0f, 255.0f, 255.0f };
		inline const Maths::Vec4 Magenta = { 255.0f, 0.0f, 255.0f, 255.0f };
		inline const Maths::Vec4 Gray = { 128.0f, 128.0f, 128.0f, 255.0f };
		inline const Maths::Vec4 Orange = { 255.0f, 166.0f, 0.0f, 255.0f };
		inline const Maths::Vec4 Purple = { 128.0f, 0.0f, 128.0f, 255.0f };
		inline const Maths::Vec4 Pink = { 255.0f, 191.0f, 204.0f, 255.0f };
		inline const Maths::Vec4 Brown = { 166.0f, 83.0f, 41.0f, 255.0f };
		inline const Maths::Vec4 Teal = { 0.0f, 128.0f, 128.0f, 255.0f };
		inline const Maths::Vec4 Silver = { 192.0f, 192.0f, 192.0f, 255.0f };
		inline const Maths::Vec4 Gold = { 255.0f, 215.0f, 0.0f, 255.0f };
		// the background color used in learnopengl.com tutorials
		inline const Maths::Vec4 DarkGreenishBlue = { 51.0f, 76.5f, 76.5f, 255.0f };
	}
}