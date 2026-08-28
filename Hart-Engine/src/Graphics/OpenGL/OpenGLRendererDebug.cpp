#include "HartPch.hpp"
#include "OpenGLRendererDebug.hpp"
#include "Utils/Logger.hpp"

namespace Hart {
	void OpenGLRendererDebug::Init() {
		HART_ENGINE_INFO(LogSource::EngineGraphics, "Initializing OpenGL Renderer Debug Context");

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLDebugMessageCallback, nullptr);
	}

	void OpenGLRendererDebug::DeInit() {
		HART_ENGINE_INFO(LogSource::EngineGraphics, "DeInitializing OpenGL Renderer Debug Context");
		glDebugMessageCallback(nullptr, nullptr);
		glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDisable(GL_DEBUG_OUTPUT);
	}

	void OpenGLRendererDebug::OpenGLDebugMessageCallback(
		GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message,
		const void* userParameter) {
		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH:
				HART_ENGINE_FATAL(
					LogSource::EngineGraphics,
					"\n\t\t\t\t\t=========OpenGL Debug Message=========",
					"\n\t\t\t\t\t  From: ", DebugSourceToString(source),
					"\n\t\t\t\t\t  Type: ", DebugTypeToString(type),
					"\n\t\t\t\t\t  OpenGL Severity: ", "HIGH",
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t======================================");
				HART_ENGINE_DEBUG_BREAK();
				break;

			case GL_DEBUG_SEVERITY_MEDIUM:
				HART_ENGINE_ERROR(
					LogSource::EngineGraphics,
					"\n\t\t\t\t\t=========OpenGL Debug Message=========",
					"\n\t\t\t\t\t  From: ", DebugSourceToString(source),
					"\n\t\t\t\t\t  Type: ", DebugTypeToString(type),
					"\n\t\t\t\t\t  OpenGL Severity: ", "MEDIUM",
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t======================================");
				break;

			case GL_DEBUG_SEVERITY_LOW:
				HART_ENGINE_WARNING(
					LogSource::EngineGraphics,
					"\n\t\t\t\t\t=========OpenGL Debug Message=========",
					"\n\t\t\t\t\t  From: ", DebugSourceToString(source),
					"\n\t\t\t\t\t  Type: ", DebugTypeToString(type),
					"\n\t\t\t\t\t  OpenGL Severity: ", "LOW",
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t======================================");
				break;

			case GL_DEBUG_SEVERITY_NOTIFICATION:
				HART_ENGINE_INFO(
					LogSource::EngineGraphics,
					"\n\t\t\t\t\t=========OpenGL Debug Message=========",
					"\n\t\t\t\t\t  From: ", DebugSourceToString(source),
					"\n\t\t\t\t\t  Type: ", DebugTypeToString(type),
					"\n\t\t\t\t\t  OpenGL Severity: ", "NOTIFICATION",
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t======================================");
				break;

			default:
				HART_ENGINE_ERROR(
					LogSource::EngineGraphics,
					"\n\t\t\t\t\t=========OpenGL Debug Message=========",
					"\n\t\t\t\t\t  From: ", DebugSourceToString(source),
					"\n\t\t\t\t\t  Type: ", DebugTypeToString(type),
					"\n\t\t\t\t\t  OpenGL Severity: ", "UNKNOWN",
					"\n\t\t\t\t\t  OpenGL Message: ", message,
					"\n\t\t\t\t\t======================================");
				break;
		}
	}

	std::string_view OpenGLRendererDebug::DebugSourceToString(GLenum source) {
		switch (source) {
			case GL_DEBUG_SOURCE_API:
				return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				return "WINDOW SYSTEM";
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				return "SHADER COMPILER";
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				return "THIRD PARTY";
			case GL_DEBUG_SOURCE_APPLICATION:
				return "APPLICATION";
			case GL_DEBUG_SOURCE_OTHER:
			default:
				return "UNKNOWN";
		}
	}

	std::string_view OpenGLRendererDebug::DebugTypeToString(GLenum type) {
		switch (type) {
			case GL_DEBUG_TYPE_ERROR:
				return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				return "DEPRECATED BEHAVIOR";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				return "UNDEFINED BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY:
				return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE:
				return "PERFORMANCE";
			case GL_DEBUG_TYPE_OTHER:
				return "OTHER";
			case GL_DEBUG_TYPE_MARKER:
			default:
				return "UNKNOWN";
		}
	}
}
