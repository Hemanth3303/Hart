#version 460 core

out vec4 FragColor;

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

void main() {
	FragColor = mix(texture(uTexture1, vTexCoord), texture(uTexture2, vTexCoord), 0.2);
//	FragColor = vColor;
}