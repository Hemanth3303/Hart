#pragma once

#include "HartPch.hpp"
#include "buffers/Buffer.hpp"
#include "buffers/IndexBuffer.hpp"
#include "buffers/VertexArray.hpp"
#include "Shader.hpp"
#include "Maths/Maths.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class Renderable2D {
		public:
			Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, Shader& shader);
			Renderable2D(const Renderable2D&) = delete;
			virtual ~Renderable2D();

			inline const Maths::Vec3& getPosition() const { return m_Position; }
			inline const Maths::Vec2& getSize() const { return m_Size; }
			inline const Maths::Vec4& getColor() const { return m_Color; }

			inline const Shader& getShader() const { return m_Shader; }
			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }

		protected:
			Maths::Vec3 m_Position;
			Maths::Vec2 m_Size;
			Maths::Vec4 m_Color;

			VertexArray* m_VertexArray = nullptr;
			IndexBuffer* m_IndexBuffer = nullptr;
			Shader& m_Shader;
		};
	}
}