#pragma once
#include "HartPch.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Maths/Mat4.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		enum class ShaderType {
			VertexShader = 0,
			FragmentShader = 1,
			Program = 2
		};
		class Shader {
		public:
			Shader();
			Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			~Shader();

			void bind() const;
			void unbind() const;

			void setUniform(const std::string& uniformName, bool value) const;
			void setUniform(const std::string& uniformName, int value) const;
			void setUniform(const std::string& uniformName, float value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec2& value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec3& value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec4& value) const;
			void setUniform(const std::string& uniformName, const Maths::Mat4& value) const;

		private:
			void init(const char* vsSource, const char* fsSource);
			int32_t getUniformLocation(const std::string& uniformName) const;
			void checkCompileErrors(uint32_t shader, const ShaderType& type) const;
		private:
			uint32_t m_ShaderID = 0;
			mutable std::unordered_map<std::string, int32_t> m_UniformLocationCache;
		};
	}
}