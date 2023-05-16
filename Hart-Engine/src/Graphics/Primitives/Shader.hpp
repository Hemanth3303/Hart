#pragma once
#include "HartPch.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Maths/Mat4.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {

		enum class ShaderDataType {
			None = 0,
			Float,
			Float2,
			Float3,
			Float4,
			Mat4,
			Int,
			Int2,
			Int3,
			Int4,
			Bool,
		};

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
			void setUniform(const std::string& uniformName, std::int32_t value) const;
			void setUniform(const std::string& uniformName, float value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec2& value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec3& value) const;
			void setUniform(const std::string& uniformName, const Maths::Vec4& value) const;
			void setUniform(const std::string& uniformName, const Maths::Mat4& value) const;

			static std::uint32_t GetShaderDataTypeSize(ShaderDataType type);
			static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type);
		private:
			void init(const char* vsSource, const char* fsSource);
			std::int32_t getUniformLocation(const std::string& uniformName) const;
			void checkCompileErrors(std::uint32_t shader, const ShaderType& type) const;
		private:
			std::uint32_t m_ShaderID = 0;
			mutable std::unordered_map<std::string, std::int32_t> m_UniformLocationCache;
		};
	}
}