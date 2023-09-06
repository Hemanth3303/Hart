#include "HartPch.hpp"
#include "HartApplication.hpp"

// initializes engine's shader library with some defaul shaders
namespace Hart {
	std::string quadShader2DVertexSource = // vertex shader
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

			uniform mat4 uViewProjectionMatrix2D;

			void main() {
				gl_Position = uViewProjectionMatrix2D * aPosition;
				vs_out.color = aColor;
				vs_out.textureCoords = aTextureCoords;
				vs_out.textureIndex = aTextureIndex;
				vs_out.tilingFactor = aTilingFactor;
			}
		)";

	std::string quadShader2DFragmentSource = // fragment shader
		R"(
			#version 460 core

			layout (location = 0) out vec4 color;

			in DATA {
				vec4 color;
				vec2 textureCoords;
				float textureIndex;
				float tilingFactor;
			} fs_in;
			
			// It used to be a single "uniform sampler2D uTextuers[32];".
			// And it worked on my laptop's Nvidia 1650 dGPU and intel uhd iGPU on my family pc.
			// But for some reason, it causes weird white artifacts in my laptop's AMD iGPU.
			// So we are left with this mess
			uniform sampler2D uTexture0;
			uniform sampler2D uTexture1;
			uniform sampler2D uTexture2;
			uniform sampler2D uTexture3;
			uniform sampler2D uTexture4;
			uniform sampler2D uTexture5;
			uniform sampler2D uTexture6;
			uniform sampler2D uTexture7;
			uniform sampler2D uTexture8;
			uniform sampler2D uTexture9;
			uniform sampler2D uTexture10;
			uniform sampler2D uTexture11;
			uniform sampler2D uTexture12;
			uniform sampler2D uTexture13;
			uniform sampler2D uTexture14;
			uniform sampler2D uTexture15;

			void main() {
				switch(int(fs_in.textureIndex)) {
					case 0:
						color = texture(uTexture0, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 1:
						color = texture(uTexture1, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 2:
						color = texture(uTexture2, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 3:
						color = texture(uTexture3, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 4:
						color = texture(uTexture4, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 5:
						color = texture(uTexture5, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 6:
						color = texture(uTexture6, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 7:
						color = texture(uTexture7, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 8:
						color = texture(uTexture8, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 9:
						color = texture(uTexture9, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 10:
						color = texture(uTexture10, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 11:
						color = texture(uTexture11, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 12:
						color = texture(uTexture12, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 13:
						color = texture(uTexture13, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 14:
						color = texture(uTexture14, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					case 15:
						color = texture(uTexture15, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
					default:
						color = texture(uTexture0, fs_in.textureCoords * fs_in.tilingFactor) * fs_in.color;
						break;
				}
			}
		)";

	std::string lineShader2DVertexSource = // vertex shader
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

	std::string lineShader2DFragmentSource = // fragment shader
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

	std::string cubeShader3DVertexSource =  // vertex shader
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

	std::string cubeShader3DFragmentSource =  // fragment shader
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

	void initializeShaderLibrary() {
		Application::Get()->m_ShaderLibrary.loadShaderFromString("QuadShader2D", quadShader2DVertexSource.c_str(), quadShader2DFragmentSource.c_str());

		Application::Get()->m_ShaderLibrary.loadShaderFromString("LineShader2D", lineShader2DVertexSource.c_str(), lineShader2DFragmentSource.c_str());

		Application::Get()->m_ShaderLibrary.loadShaderFromString("CubeShader3D", cubeShader3DVertexSource.c_str(), cubeShader3DFragmentSource.c_str());
	}
}