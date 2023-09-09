#pragma once

#include "HartPch.hpp"

namespace Hart {
	inline const std::string CubeShader3DVertexSource =  // vertex shader
		R"(
			#version 460 core
			
			layout (location = 0) in vec3 aPosition;
			layout (location = 1) in vec4 aColor;

			out DATA {
				vec4 color;
			} vs_out;

			uniform mat4 uViewProjectionMatrix3D;
			uniform mat4 uModelMatrix = mat4(1.0);
			
			void main() {
				gl_Position = uViewProjectionMatrix3D * uModelMatrix * vec4(aPosition, 1.0);
				vs_out.color = aColor;
			}
		)";

	inline const std::string CubeShader3DFragmentSource =  // fragment shader
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