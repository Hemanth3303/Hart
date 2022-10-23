/*
* Base class for all 2d renderables
*/

#pragma once

#include "HartPch.hpp"
#include "buffers/Buffer.hpp"
#include "buffers/IndexBuffer.hpp"
#include "buffers/VertexArray.hpp"
#include "Renderer2D.hpp"
#include "Shader.hpp"
#include "Maths/Maths.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		using Color = Hart::Maths::Vec4;

		struct VertexData {
		public:
			Maths::Vec3 vertex;
			uint32_t color;
		};

		class Renderable2D {
		public:
			Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Color& color)
				:m_Position(position), m_Size(size), m_Color(color) {

			}

			virtual ~Renderable2D() {

			}

			virtual void submit(Renderer2D* renderer2d) const {
				renderer2d->submit(this);
			}

			inline const Maths::Vec3& getPosition() const { return m_Position; }
			inline const Maths::Vec2& getSize() const { return m_Size; }
			inline const Color& getColor() const { return m_Color; }
		protected:
			Renderable2D() {

			}
		protected:
			Maths::Vec3 m_Position;
			Maths::Vec2 m_Size;
			Maths::Vec4 m_Color;
		};
	}
}