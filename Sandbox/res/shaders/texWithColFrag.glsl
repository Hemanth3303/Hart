#version 460 core

out vec4 FragColor;

in vec4 outColor;
in vec2 texCoord;

uniform sampler2D gameTexture1;

void main() {
	FragColor = texture(gameTexture1, texCoord) * outColor;
}