#version 460 core

out vec4 FragColor;

in vec4 outColor;
in vec2 texCoord;

uniform sampler2D gameTexture1;
uniform sampler2D gameTexture2;

void main() {
//	FragColor = texture(gameTexture, texCoord) * outColor;
//	FragColor = texture(gameTexture1, texCoord);
//	FragColor = mix(texture(gameTexture1, texCoord), texture(gameTexture2, texCoord), 0.5);
	FragColor = mix(texture(gameTexture1, texCoord), texture(gameTexture2, texCoord), 0.5) * outColor;
}