#include "HartPch.hpp"
#include "HartApplication.hpp"

// initializes engine's shader library with some defaul shaders
namespace Hart {

	std::string basicShader2DVertexSource = // vertex shader
		R"(
			#version 460 core

			layout (location = 0) in vec3 aPosition;

			uniform mat4 uModelMatrix=mat4(1.0);
			uniform mat4 uViewProjectionMatrix;

			void main() {
				gl_Position = uViewProjectionMatrix * uModelMatrix * vec4(aPosition, 1.0);
			}
		)";

	std::string basicShader2DFragmentSource = // fragment shader
		R"(
			#version 460 core

			out vec4 FragColor;

			uniform vec4 vColor;

			void main() {
				FragColor = vColor;
			}
		)";

	std::string defaultShader2DVertexSource = // vertex shader
		R"(
			#version 460 core

			layout (location = 0) in vec3 aPosition;
			layout (location = 1) in vec2 aTexCoord;

			out vec2 vTexCoord;

			uniform mat4 uModelMatrix=mat4(1.0);
			uniform mat4 uViewProjectionMatrix;

			void main() {
				gl_Position = uViewProjectionMatrix * uModelMatrix * vec4(aPosition, 1.0);
				vTexCoord=aTexCoord;
			}
		)";

	std::string defaultShader2DFragmentSource = // fragment shader
		R"(
			#version 460 core

			out vec4 FragColor;

			in vec4 vColor;
			in vec2 vTexCoord;

			uniform vec4 uColor;
			uniform float uTextureTilingFactor = 1;
			uniform sampler2D uTexture;

			void main() {
				FragColor = texture(uTexture, vTexCoord * uTextureTilingFactor) * uColor;
			}
		)";

	void initializeShaderLibrary() {
		Application::s_Instance->m_ShaderLibrary.loadShaderFromString("DefaultShader2D", defaultShader2DVertexSource.c_str(), defaultShader2DFragmentSource.c_str());
		Application::s_Instance->m_ShaderLibrary.loadShaderFromString("BasicShader2D", basicShader2DVertexSource.c_str(), basicShader2DFragmentSource.c_str());
	}
}