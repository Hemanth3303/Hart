#include "HartPch.hpp"
#include "HartApplication.hpp"

// initializes engine's shader library with some defaul shaders
namespace Hart {
	std::string defaultShader2DVertexSource = // vertex shader
		R"(
			#version 460 core

			layout (location = 0) in vec4 aPosition;
			layout (location = 1) in vec4 aColor;
			layout (location = 2) in vec2 aTextureCoords;
			layout (location = 3) in float aTextureIndex;
			layout (location = 4) in float aTilingFactor;

			out DATA {
				vec4 color;
				vec2 textureCoords;
				float textureIndex;
				float tilingFactor;
			} vs_out;

			uniform mat4 uViewProjectionMatrix;

			void main() {
				gl_Position = uViewProjectionMatrix * aPosition;
				vs_out.color=aColor;
				vs_out.textureCoords=aTextureCoords;
				vs_out.textureIndex=aTextureIndex;
				vs_out.tilingFactor=aTilingFactor;
			}
		)";

	std::string defaultShader2DFragmentSource = // fragment shader
		R"(
			#version 460 core

			layout (location = 0) out vec4 color;

			in DATA {
				vec4 color;
				vec2 textureCoords;
				float textureIndex;
				float tilingFactor;
			} fs_in;

			uniform sampler2D uTextures[32];

			void main() {
				color = texture(uTextures[int(fs_in.textureIndex)], fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
			}
		)";

	void initializeShaderLibrary() {
		Application::s_Instance->m_ShaderLibrary.loadShaderFromString("DefaultShader2D", defaultShader2DVertexSource.c_str(), defaultShader2DFragmentSource.c_str());
	}
}