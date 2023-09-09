#pragma once

#include "HartPch.hpp"

namespace Hart {
	inline const std::string LineShader2DVertexSource = // vertex shader
		R"(
			#version 460 core

			layout (location = 0) in vec4 aPosition;
			layout (location = 1) in vec4 aColor;

			out DATA {
				vec4 color;
			} vs_out;

			uniform mat4 uViewProjectionMatrix2D;

			void main() {
				gl_Position = uViewProjectionMatrix2D * aPosition;
				vs_out.color = aColor;
			}
		)";

	inline const std::string LineShader2DFragmentSource = // fragment shader
		R"(
			#version 460 core

			layout (location = 0) out vec4 color;

			in DATA {
				vec4 color;
			} fs_in;

			void main() {
				color = fs_in.color;
			}
		)";
}