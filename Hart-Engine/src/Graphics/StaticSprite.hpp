/*
* A class denoting objects that won't change it's transform or color after instansiation
*/

#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		class StaticSprite : public Renderable2D {
		public:
			StaticSprite(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, Shader& shader);
			StaticSprite(const StaticSprite&) = delete;
			~StaticSprite();

			inline const Shader& getShader() const { return m_Shader; }
			inline const std::unique_ptr<VertexArray>& getVAO() const { return m_VertexArray; }
			inline const std::unique_ptr<IndexBuffer>& getIBO() const { return m_IndexBuffer; }
		private:
			std::unique_ptr<VertexArray> m_VertexArray;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			Shader& m_Shader;
		};
	}
}