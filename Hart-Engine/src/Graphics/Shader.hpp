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
			//uses specified shaders
			Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
			~Shader();

			void bind();
			void unbind();

			void setUniform(const std::string& uniformName, const bool& value) const;
			void setUniform(const std::string& uniformName, const int32_t& value) const;
			void setUniform(const std::string& uniformName, const float& value) const;

			void setUniform(const std::string& uniformName, const Maths::Vec2& value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec3& value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec4& value) const;
			void setUniform(const std::string& uniformName, const Maths::Mat4& value) const;

			inline const GLuint getProgramId() { return m_ProgramId; }
		private:
			void checkCompileErrors(uint32_t shader, const ShaderType& type);
			GLint getUniformLocation(const std::string& uniformName) const;
		private:
			GLuint m_ProgramId;
			mutable std::unordered_map<std::string, GLint> m_ShaderLocationCache;
		};
	}
}