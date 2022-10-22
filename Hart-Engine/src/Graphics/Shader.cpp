#include "HartPch.hpp"
#include "Shader.hpp"

namespace Hart {
	namespace Graphics {

		Shader::Shader() {
			const char* vertexCode = "#version 460 core\n"
				"layout (location = 0) in vec4 position;\n"
				"layout (location = 1) in vec4 aColor;\n"
				"\n"
				"uniform mat4 pr_matrix;\n"
				"uniform mat4 vw_matrix = mat4(1.0);\n"
				"uniform mat4 ml_matrix = mat4(1.0);\n"
				"\n"
				"out vec4 color;\n"
				"\n"
				"void main() {\n"
				"    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
				"	color = aColor;\n"
				"}\0";

			const char* fragmentCode = "#version 460 core\n"
				"out vec4 FragColor;\n"
				"\n"
				"in vec4 color;\n"
				"\n"
				"void main() {\n"
				"	FragColor = color;\n"
				"}\0";

			init(vertexCode, fragmentCode);
		}

		Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath) {
			std::string vertexSource, fragmentSource;

			vertexSource = Utils::FileManager::ReadFromFile(vertexFilePath);
			fragmentSource = Utils::FileManager::ReadFromFile(fragmentFilePath);

			const char* vertexCode = vertexSource.c_str();
			const char* fragmentCode = fragmentSource.c_str();

			init(vertexCode, fragmentCode);

		}

		Shader::~Shader() {
			glDeleteProgram(m_ProgramId);
		}

		void Shader::bind() const {
			glUseProgram(m_ProgramId);
		}

		void Shader::unbind() const {
			glUseProgram(0);
		}

		void Shader::setUniform(const std::string& uniformName, const bool& value) const {
			glUniform1i(getUniformLocation(uniformName), static_cast<int32_t>(value));
		}

		void Shader::setUniform(const std::string& uniformName, const int32_t& value) const {
			glUniform1i(getUniformLocation(uniformName), value);
		}

		void Shader::setUniform(const std::string& uniformName, const float& value) const {
			glUniform1f(getUniformLocation(uniformName), value);
		}

		void Shader::setUniform(const std::string& uniformName, const Maths::Vec2& value) const {
			glUniform2f(getUniformLocation(uniformName), value.x, value.y);
		}

		void Shader::setUniform(const std::string& uniformName, const Maths::Vec3& value) const {
			glUniform3f(getUniformLocation(uniformName), value.x, value.y, value.z);
		}

		void Shader::setUniform(const std::string& uniformName, const Maths::Vec4& value) const {
			glUniform4f(getUniformLocation(uniformName), value.x, value.y, value.z, value.w);
		}

		void Shader::setUniform(const std::string& uniformName, const Maths::Mat4& value) const {
			glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, value.elements);
		}

		void Shader::checkCompileErrors(uint32_t shader, const ShaderType& type) {
			int32_t success;
			char infoLog[2048];
			if (type != ShaderType::Program) {
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(shader, 2048, nullptr, infoLog);
					if (type == ShaderType::VertexShader) {
						HART_ENGINE_ERROR("Vertex Shader Compilation Error");
					}
					else if (type == ShaderType::FragmentShader) {
						HART_ENGINE_ERROR("Fragment Shader Compilation Error");
					}
				}
				else {
					if (type == ShaderType::VertexShader) {
						HART_ENGINE_INFO("Vertex Shader Compiled Successfully");
					}
					else if (type == ShaderType::FragmentShader) {
						HART_ENGINE_INFO("Fragment Shader Compiled Successfully");
					}
				}
			}
			else {
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(shader, 2048, nullptr, infoLog);
					HART_ENGINE_ERROR("Program Linking Error");
				}
				else {
					HART_ENGINE_INFO("Program Linked Successfully");
				}
			}
		}

		GLint Shader::getUniformLocation(const std::string& uniformName) const {
			if (m_ShaderLocationCache.find(uniformName) == m_ShaderLocationCache.end()) {
				GLint location = glGetUniformLocation(m_ProgramId, uniformName.c_str());
				m_ShaderLocationCache[uniformName] = location;
				return location;
			}
			else {
				return m_ShaderLocationCache[uniformName];
			}
		}

		void Shader::init(const char* vertexCode, const char* fragmentCode) {
			uint32_t vertexId, fragmentId;

			vertexId = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexId, 1, &vertexCode, nullptr);
			glCompileShader(vertexId);
			checkCompileErrors(vertexId, ShaderType::VertexShader);

			fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentId, 1, &fragmentCode, nullptr);
			glCompileShader(fragmentId);
			checkCompileErrors(fragmentId, ShaderType::FragmentShader);

			m_ProgramId = glCreateProgram();
			glAttachShader(m_ProgramId, vertexId);
			glAttachShader(m_ProgramId, fragmentId);
			glLinkProgram(m_ProgramId);
			checkCompileErrors(m_ProgramId, ShaderType::Program);

			glDeleteShader(vertexId);
			glDeleteShader(fragmentId);
		}

	}
}