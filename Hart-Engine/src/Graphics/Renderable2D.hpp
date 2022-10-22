/*
* Base class for all 2d renderables
*/

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

		struct VertexData {
		public:
			Maths::Vec3 vertex;
			Maths::Vec4 color;
		};

		class Renderable2D {
		public:
			Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color)
				:m_Position(position), m_Size(size), m_Color(color) {

			}

			virtual ~Renderable2D() {

			}

			inline const Maths::Vec3& getPosition() const { return m_Position; }
			inline const Maths::Vec2& getSize() const { return m_Size; }
			inline const Maths::Vec4& getColor() const { return m_Color; }


		protected:
			Maths::Vec3 m_Position;
			Maths::Vec2 m_Size;
			Maths::Vec4 m_Color;
		};
	}
}