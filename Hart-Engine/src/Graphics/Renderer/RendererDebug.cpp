#include "HartPch.hpp"
#include "RendererDebug.hpp"
#include "Utils/Logger.hpp"

namespace Hart {
	void RendererDebug::Init() {
		HART_ENGINE_INFO("Initializing OpenGL Renderer Debug Context");

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLDebugMessageCallback, nullptr);
	}

	void RendererDebug::DeInit() {
		HART_ENGINE_INFO("DeInitializing OpenGL Renderer Debug Context");
		glDebugMessageCallback(nullptr, nullptr);
		glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDisable(GL_DEBUG_OUTPUT);
	}

	void RendererDebug::OpenGLDebugMessageCallback(
		GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message,
		const void* userParameter) {
		const char* debugSource;
		const char* debugType;
		const char* debugSeverity;

		switch (source) {
			case GL_DEBUG_SOURCE_API:
				debugSource = "API";
				break;

			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				debugSource = "WINDOW SYSTEM";
				break;

			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				debugSource = "SHADER COMPILER";
				break;

			case GL_DEBUG_SOURCE_THIRD_PARTY:
				debugSource = "THIRD PARTY";
				break;

			case GL_DEBUG_SOURCE_APPLICATION:
				debugSource = "APPLICATION";
				break;

			case GL_DEBUG_SOURCE_OTHER:
				debugSource = "UNKNOWN";
				break;

			default:
				debugSource = "UNKNOWN";
				break;
		}

		switch (type) {
			case GL_DEBUG_TYPE_ERROR:
				debugType = "ERROR";
				break;

			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				debugType = "DEPRECATED BEHAVIOR";
				break;

			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				debugType = "UNDEFINED BEHAVIOR";
				break;

			case GL_DEBUG_TYPE_PORTABILITY:
				debugType = "PORTABILITY";
				break;

			case GL_DEBUG_TYPE_PERFORMANCE:
				debugType = "PERFORMANCE";
				break;

			case GL_DEBUG_TYPE_OTHER:
				debugType = "OTHER";
				break;

			case GL_DEBUG_TYPE_MARKER:
				debugType = "MARKER";
				break;

			default:
				debugType = "UNKNOWN";
				break;
		}

		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH:
				debugSeverity = "HIGH";
				HART_ENGINE_FATAL(
					"\n\t\t\t\t\t=========OpenGL Error=========",
					"\n\t\t\t\t\t  From: ", debugSource,
					"\n\t\t\t\t\t  Type: ", debugType,
					"\n\t\t\t\t\t  OpenGL Severity: ", debugSeverity,
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t===============================");
				HART_ENGINE_DEBUG_BREAK();
				break;

			case GL_DEBUG_SEVERITY_MEDIUM:
				debugSeverity = "MEDIUM";
				HART_ENGINE_ERROR(
					"\n\t\t\t\t\t=========OpenGL Error=========",
					"\n\t\t\t\t\t  From: ", debugSource,
					"\n\t\t\t\t\t  Type: ", debugType,
					"\n\t\t\t\t\t  OpenGL Severity: ", debugSeverity,
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t===============================");
				break;

			case GL_DEBUG_SEVERITY_LOW:
				debugSeverity = "LOW";
				HART_ENGINE_WARNING(
					"\n\t\t\t\t\t=========OpenGL Error=========",
					"\n\t\t\t\t\t  From: ", debugSource,
					"\n\t\t\t\t\t  Type: ", debugType,
					"\n\t\t\t\t\t  OpenGL Severity: ", debugSeverity,
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t===============================");
				break;

			case GL_DEBUG_SEVERITY_NOTIFICATION:
				debugSeverity = "NOTIFICATION";
				HART_ENGINE_INFO(
					"\n\t\t\t\t\t=========OpenGL Error=========",
					"\n\t\t\t\t\t  From: ", debugSource,
					"\n\t\t\t\t\t  Type: ", debugType,
					"\n\t\t\t\t\t  OpenGL Severity: ", debugSeverity,
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t===============================");
				break;

			default:
				debugSeverity = "UNKNOWN";
				HART_ENGINE_ERROR(
					"\n\t\t\t\t\t=========OpenGL Error=========",
					"\n\t\t\t\t\t  From: ", debugSource,
					"\n\t\t\t\t\t  Type: ", debugType,
					"\n\t\t\t\t\t  OpenGL Severity: ", debugSeverity,
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t===============================");
				break;
		}
	}
}
