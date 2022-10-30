#pragma once

#include "HartPch.hpp"
#include "Maths/Maths.hpp"
#include "Utils/FileManager.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		enum class ShaderType {
			Program = 0,
			VertexShader,
			FragmentShader,
		};
		class Shader {
		public:
			//uses default shaders
			Shader();
			//uses specified shaders
			Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
			Shader(const Shader&) = delete;
			~Shader();

			void enable() const;
			void disable() const;

			void setUniform(const std::string& uniformName, const bool& value) const;
			void setUniform(const std::string& uniformName, const int32_t& value) const;
			void setUniform(const std::string& uniformName, const float& value) const;

			void setUniform(const std::string& uniformName, const Maths::Vec2& value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec3& value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec4& value) const;
			void setUniform(const std::string& uniformName, const Maths::Mat4& value) const;

			inline const GLuint getProgramID() { return m_ProgramID; }
		private:
			void checkCompileErrors(uint32_t shader, const ShaderType& type);
			GLint getUniformLocation(const std::string& uniformName) const;

			void init(const char* vertexCode, const char* fragmentCode);
		private:
			GLuint m_ProgramID;
			mutable std::unordered_map<std::string, GLint> m_ShaderLocationCache;
		};
	}
}