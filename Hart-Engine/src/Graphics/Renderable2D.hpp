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
		struct VertexData {
		public:
			VertexData(const Maths::Vec3& p_position, const Maths::Vec2& p_size, const Maths::Vec4& p_color) 
				:position(p_position), size(p_size), color(p_color) {

			}
		public:
			Maths::Vec3 position;
			Maths::Vec2 size;
			Maths::Vec4 color;
		};
		class Renderable2D {
		protected:
			Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color);
		public:
			virtual ~Renderable2D();
			IndexBuffer* getIndexBuffer() const { return m_IndexBuffer.get(); }
			VertexArray* getVertexArray() const { return m_VertexArray.get(); }

			const Maths::Vec3& getPosition() const { return m_VertexData.position; }
			const Maths::Vec2& getSize() const { return m_VertexData.size; }
			const Maths::Vec4& getColor() const { return m_VertexData.color; }
		protected:
			VertexData m_VertexData;

			VertexBuffer m_VertexBuffer, m_ColorBuffer;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			std::unique_ptr<VertexArray> m_VertexArray;
		};
	}
}