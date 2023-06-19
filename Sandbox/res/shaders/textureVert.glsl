#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 vColor;
out vec2 vTexCoord;

uniform mat4 uModelMatrix=mat4(1.0);
uniform mat4 uViewProjectionMatrix;

void main() {
	gl_Position = uViewProjectionMatrix * uModelMatrix * vec4(aPosition, 1.0);
	vColor = aColor;
	vTexCoord=aTexCoord;
}