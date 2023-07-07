#include "HartPch.hpp"
#include "HartApplication.hpp"

// initializes engine's shader library with some defaul shaders
namespace Hart {
	std::string defaultShader2DVertexSource = // vertex shader
		R"(
			#version 460 core

			layout (location = 0) in vec3 aPosition;
			layout (location = 1) in vec4 aColor;
			layout (location = 2) in vec2 aTextureCoords;
			layout (location = 3) in float aTextureIndex;

			out vec4 vColor;
			out vec2 vTextureCoords;
			out float vTextureIndex;

			uniform mat4 uViewProjectionMatrix;

			void main() {
				gl_Position = uViewProjectionMatrix * vec4(aPosition, 1.0);
				vColor=aColor;
				vTextureCoords=aTextureCoords;
				vTextureIndex=aTextureIndex;
			}
		)";

	std::string defaultShader2DFragmentSource = // fragment shader
		R"(
			#version 460 core

			layout (location = 0) out vec4 color;

			in vec4 vColor;
			in vec2 vTextureCoords;
			in float vTextureIndex;

			uniform sampler2D uTextures[32];

			void main() {
				color = texture(uTextures[int(vTextureIndex)], vTextureCoords) * vColor;
			}
		)";

	void initializeShaderLibrary() {
		Application::s_Instance->m_ShaderLibrary.loadShaderFromString("DefaultShader2D", defaultShader2DVertexSource.c_str(), defaultShader2DFragmentSource.c_str());
	}
}