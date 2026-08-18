#pragma once

#include "glad/glad.h"

namespace Hart {
	class RendererDebug {
	public:
		static void Init();
		static void DeInit();

	private:
		// based on https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f
		static void OpenGLDebugMessageCallback(
			GLenum source, GLenum type, GLuint id,
			GLenum severity, GLsizei length, const GLchar* message,
			const void* userParameter);
	};
}
