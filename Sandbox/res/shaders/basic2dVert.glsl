#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

out vec4 vColor;

uniform mat4 uModelMatrix=mat4(1.0);
uniform mat4 uViewProjectionMatrix;

void main() {
	gl_Position = uViewProjectionMatrix * uModelMatrix * vec4(aPosition, 1.0);
	vColor = aColor;
}