/*
* Something that is rendered by a 2d renderer
*/

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
			Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, std::shared_ptr<Shader> shader);
			~Renderable2D();

			Shader* getShader() const { return m_Shader.get(); }
			IndexBuffer* getIndexBuffer() const { return m_IndexBuffer.get(); }
			VertexArray* getVertexArray() const { return m_VertexArray.get(); }

			const Maths::Vec3& getPosition() const { return m_Position; }
			const Maths::Vec2& getSize() const { return m_Size; }
			const Maths::Vec4& getColor() const { return m_Color; }

		private:
			Maths::Vec3 m_Position;
			Maths::Vec2 m_Size;
			Maths::Vec4 m_Color;

			std::shared_ptr<Shader> m_Shader;
			VertexBuffer m_VertexBuffer, m_ColorBuffer;
			std::shared_ptr<IndexBuffer> m_IndexBuffer;
			std::shared_ptr<VertexArray> m_VertexArray;
		};
	}
}