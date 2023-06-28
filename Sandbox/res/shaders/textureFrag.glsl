#version 460 core

out vec4 FragColor;

in vec4 vColor;
in vec2 vTexCoord;

uniform vec4 uColor;
uniform float uTextureTilingScale = 1;
uniform sampler2D uTexture;

void main() {
	FragColor = texture(uTexture, vTexCoord * uTextureTilingScale) * uColor;
}