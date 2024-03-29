#pragma once

#include "HartPch.hpp"

namespace Hart {
	inline const std::string QuadShader2DVertexSource = // vertex shader
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

	inline const std::string QuadShader2DFragmentSource = // fragment shader
		R"(
			#version 460 core

			layout (location = 0) out vec4 color;

			in DATA {
				vec4 color;
				vec2 textureCoords;
				float textureIndex;
				float tilingFactor;
			} fs_in;
			
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
}