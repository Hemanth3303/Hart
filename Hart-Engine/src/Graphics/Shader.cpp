/*
* Based on shader class from learnopengl.com
* https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h
*/

#include "HartPch.hpp"
#include "Shader.hpp"

namespace Hart {
	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
		std::string vertexShaderString = FileManager::ReadStringFromFile(vertexShaderPath);
		std::string fragmentShaderString = FileManager::ReadStringFromFile(fragmentShaderPath);

		m_Name = FileManager::GetFileName(vertexShaderPath);
		init(vertexShaderString.c_str(), fragmentShaderString.c_str());
	}

	Shader::Shader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
		: m_Name(name) {
		std::string vertexShaderString = FileManager::ReadStringFromFile(vertexShaderPath);
		std::string fragmentShaderString = FileManager::ReadStringFromFile(fragmentShaderPath);

		init(vertexShaderString.c_str(), fragmentShaderString.c_str());
	}

	Shader::Shader(const std::string& name, const char* vertexShaderSource, const char* fragmentShaderSource)
		:m_Name(name) {

		init(vertexShaderSource, fragmentShaderSource);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderID);
	}

	void Shader::bind() const {
		glUseProgram(m_ShaderID);
	}

	void Shader::unbind() const {
		glUseProgram(0);
	}

	void Shader::setUniform(const std::string& uniformName, bool value) const {
		glUniform1i(getUniformLocation(uniformName), static_cast<std::int32_t>(value));
	}

	void Shader::setUniform(const std::string& uniformName, std::int32_t value) const {
		glUniform1i(getUniformLocation(uniformName), value);
	}

	void Shader::setUniform(const std::string& uniformName, std::int32_t* values, std::uint32_t count) const {
		glUniform1iv(getUniformLocation(uniformName), count, values);
	}

	void Shader::setUniform(const std::string& uniformName, float value) const {
		glUniform1f(getUniformLocation(uniformName), value);
	}

	void Shader::setUniform(const std::string& uniformName, const Vec2& value) const {
		glUniform2f(getUniformLocation(uniformName), value.x, value.y);
	}

	void Shader::setUniform(const std::string& uniformName, const Vec3& value) const {
		glUniform3f(getUniformLocation(uniformName), value.x, value.y, value.z);
	}

	void Shader::setUniform(const std::string& uniformName, const Vec4& value) const {
		glUniform4f(getUniformLocation(uniformName), value.x, value.y, value.z, value.w);
	}

	void Shader::setUniform(const std::string& uniformName, const Mat4& value) const {
		glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, value.elements);
	}

	std::uint32_t Shader::GetShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case Hart::ShaderDataType::None:
				HART_ENGINE_ERROR("Can't have ShaderDataType==None");
				return 0;
			case Hart::ShaderDataType::Float:
				return 4;
			case Hart::ShaderDataType::Float2:
				return 4 * 2;
			case Hart::ShaderDataType::Float3:
				return 4 * 3;
			case Hart::ShaderDataType::Float4:
				return 4 * 4;
			case Hart::ShaderDataType::Mat4:
				return 4 * 4 * 4;
			case Hart::ShaderDataType::Int:
				return 4;
			case Hart::ShaderDataType::Int2:
				return 4 * 2;
			case Hart::ShaderDataType::Int3:
				return 4 * 3;
			case Hart::ShaderDataType::Int4:
				return 4 * 4;
			case Hart::ShaderDataType::Bool:
				return 1;
			default:
				HART_ENGINE_ERROR("Unknown ShaderDataType");
				return 0;
		}
	}

	GLenum Shader::ShaderDataTypeToOpenGLType(ShaderDataType type) {
		switch (type) {
			case Hart::ShaderDataType::None:
				HART_ENGINE_ERROR("ShaderDataType can't be null");
				return GL_INVALID_ENUM;
			case Hart::ShaderDataType::Float:
				return GL_FLOAT;
			case Hart::ShaderDataType::Float2:
				return GL_FLOAT;
			case Hart::ShaderDataType::Float3:
				return GL_FLOAT;
			case Hart::ShaderDataType::Float4:
				return GL_FLOAT;
			case Hart::ShaderDataType::Mat4:
				return GL_FLOAT;
			case Hart::ShaderDataType::Int:
				return GL_INT;
			case Hart::ShaderDataType::Int2:
				return GL_INT;
			case Hart::ShaderDataType::Int3:
				return GL_INT;
			case Hart::ShaderDataType::Int4:
				return GL_INT;
			case Hart::ShaderDataType::Bool:
				return GL_BOOL;
			default:
				HART_ENGINE_ERROR("Unknown ShaderDataType");
				return GL_INVALID_ENUM;
		}
	}

	void Shader::init(const char* vsSource, const char* fsSource) {
		const char* vertexShaderSource = vsSource;
		const char* fragmentShaderSource = fsSource;

		std::uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader, ShaderType::VertexShader);

		std::uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);
		checkCompileErrors(fragmentShader, ShaderType::FragmentShader);

		m_ShaderID = glCreateProgram();
		glAttachShader(m_ShaderID, vertexShader);
		glAttachShader(m_ShaderID, fragmentShader);
		glLinkProgram(m_ShaderID);
		checkCompileErrors(m_ShaderID, ShaderType::Program);

		glDetachShader(m_ShaderID, vertexShader);
		glDetachShader(m_ShaderID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	std::int32_t Shader::getUniformLocation(const std::string& uniformName) const {
		if (m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end()) {
			return m_UniformLocationCache[uniformName];
		}

		std::int32_t uniformLocation = glGetUniformLocation(m_ShaderID, uniformName.c_str());
		m_UniformLocationCache[uniformName] = uniformLocation;
		return uniformLocation;
	}

	void Shader::checkCompileErrors(std::uint32_t shader, const ShaderType& type) const {
		std::int32_t success;
		constexpr size_t INFOLOG_SIZE = 2048;
		char infoLog[INFOLOG_SIZE];

		if (type != ShaderType::Program) {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, INFOLOG_SIZE, nullptr, infoLog);
				if (type == ShaderType::VertexShader) {
					HART_ENGINE_ERROR("Vertex Shader Compile Error", infoLog);
				}
				else {
					HART_ENGINE_ERROR("Fragment Shader Compile Error", infoLog);
				}
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, INFOLOG_SIZE, nullptr, infoLog);
				HART_ENGINE_ERROR("Shader Program Link Error", infoLog);
			}
		}
	}
}