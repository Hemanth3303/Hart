#pragma once

#include "HartPch.hpp"
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"

namespace Hart {
	namespace Graphics {
		class Renderable2D {
		public:
			Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, Shader* shader);
			~Renderable2D();

			Shader* getShader() const { return m_Shader; }
			IndexBuffer* getIndexBuffer() const { return m_IndexBuffer; }
			VertexArray* getVertexArray() const { return m_VertexArray; }

			const Maths::Vec3& getPosition() const { return m_Position; }
			const Maths::Vec2& getSize() const { return m_Size; }
			const Maths::Vec4& getColor() const { return m_Color; }

		private:
			Maths::Vec3 m_Position;
			Maths::Vec2 m_Size;
			Maths::Vec4 m_Color;

			Shader* m_Shader;
			VertexBuffer m_VertexBuffer, m_ColorBuffer;
			IndexBuffer* m_IndexBuffer;
			VertexArray* m_VertexArray;
		};
	}
}