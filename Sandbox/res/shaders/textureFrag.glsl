#version 460 core

out vec4 FragColor;

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D gameTexture1;

void main() {
	//FragColor = texture(gameTexture1, vTexCoord);
	FragColor = vColor;
}