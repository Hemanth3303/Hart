/*
* A 2d quad that is rendered by a 2d renderer
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
		class Renderer2D;
		struct VertexData {
		public:
			Maths::Vec3 position;
			Maths::Vec2 size;
			uint32_t color;
		};
		class Renderable2D {
		public:
			Renderable2D();
			Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color);
			Renderable2D(float x, float y, float width, float height, const Maths::Vec4& color);
			virtual ~Renderable2D();

			virtual void submit(Renderer2D* render) const;

			IndexBuffer* getIndexBuffer() const { return m_IndexBuffer.get(); }
			VertexArray* getVertexArray() const { return m_VertexArray.get(); }

			const Maths::Vec3& getPosition() const { return m_Position; }
			const Maths::Vec2& getSize() const { return m_Size; }
			const Maths::Vec4& getColor() const { return m_Color; }
		protected:
			Maths::Vec3 m_Position;
			Maths::Vec2 m_Size;
			Maths::Vec4 m_Color;

			VertexBuffer m_VertexBuffer, m_ColorBuffer;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			std::unique_ptr<VertexArray> m_VertexArray;
		};
	}
}