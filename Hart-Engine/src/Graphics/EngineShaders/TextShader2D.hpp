#pragma once

#include "HartPch.hpp"

namespace Hart {
	inline const std::string TextShader2DVertexSource = // vertex shader
		R"(
			#version 460 core

			layout (location = 0) in vec4 aPosition;
			layout (location = 1) in vec4 aColor;
			layout (location = 2) in vec2 aTextureCoords;

			out DATA {
				vec4 color;
				vec2 textureCoords;
			} vs_out;

			uniform mat4 uViewProjectionMatrix2D;

			void main() {
				gl_Position = uViewProjectionMatrix2D * aPosition;
				vs_out.color = aColor;
				vs_out.textureCoords = aTextureCoords;
			}
		)";

	inline const std::string TextShader2DFragmentSource = // fragment shader
		R"(
			#version 460 core

			layout (location = 0) out vec4 color;

			in DATA {
				vec4 color;
				vec2 textureCoords;
			} fs_in;
			
			uniform sampler2D uTexture16;

			void main() {
				float value = texture(uTexture16, fs_in.textureCoords).r;
				color = vec4(value, value, value, value) * fs_in.color;
			}
		)";
}