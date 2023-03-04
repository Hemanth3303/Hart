#include "HartPch.hpp"
#include "StaticRenderable2D.hpp"

namespace Hart {
	namespace Graphics {
		StaticRenderable2D::StaticRenderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, std::shared_ptr<Shader> shader)
			:Renderable2D(position, size, color), m_Shader(shader) {

			float vertices[12] = {
				position.x + size.x / 2,  position.y + size.y / 2, position.z,  // top right | index=0
				position.x + size.x / 2,  position.y - size.y / 2, position.z,  // bottom right | index=1
				position.x - size.x / 2,  position.y - size.y / 2, position.z,  // bottom left | index=2 
				position.x - size.x / 2,  position.y + size.y / 2, position.z   // top left | index=3
			};
			float colors[16] = {
				color.x, color.y, color.z, color.w,  // top right | index=0
				color.x, color.y, color.z, color.w,  // bottom right | index=1
				color.x, color.y, color.z, color.w,  // bottom left | index=2
				color.x, color.y, color.z, color.w,  // top left | index=3
			};
			uint32_t indices[6] = {
				0, 1, 3,
				1, 2, 3,
			};

			m_VertexArray = std::make_unique<VertexArray>();
			m_VertexArray->bind();

			m_VertexBuffer.bind();
			m_VertexArray->setVertexData(0, 3, 12 * sizeof(float), 0, vertices, GL_STATIC_DRAW);
			m_VertexBuffer.unbind();

			m_ColorBuffer.bind();
			m_VertexArray->setVertexData(1, 4, 16 * sizeof(float), 0, colors, GL_STATIC_DRAW);
			m_ColorBuffer.unbind();

			m_IndexBuffer = std::make_unique<IndexBuffer>(6);
			m_IndexBuffer->bind();
			m_VertexArray->setIndexData(6, indices, GL_STATIC_DRAW);
			m_IndexBuffer->unbind();

			m_VertexArray->unbind();

		}

		StaticRenderable2D::~StaticRenderable2D() {

		}
	}
}