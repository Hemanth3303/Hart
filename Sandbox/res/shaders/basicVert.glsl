#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

out vec4 vColor;

uniform mat4 model=mat4(1.0);
uniform mat4 view=mat4(1.0);
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPosition, 1.0);
	vColor = aColor;
}