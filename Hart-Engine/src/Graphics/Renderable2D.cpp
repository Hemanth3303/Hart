#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		Renderable2D::Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, std::shared_ptr<Shader> shader)
			:m_Position(position), m_Size(size), m_Color(color), m_Shader(shader) {

			float vertices[12] = {
				m_Position.x + m_Size.x,  m_Position.y + m_Size.y, m_Position.z,  // top right 0
				m_Position.x + m_Size.x,  m_Position.y - m_Size.y, m_Position.z,  // bottom right 1
				m_Position.x - m_Size.x,  m_Position.y - m_Size.y, m_Position.z,  // bottom left 2 
				m_Position.x - m_Size.x,  m_Position.y + m_Size.y, m_Position.z   // top left 3
			};
			float colors[16] = {
				m_Color.x, m_Color.y, m_Color.z, m_Color.w,  // top right 0
				m_Color.x, m_Color.y, m_Color.z, m_Color.w,  // bottom right 1
				m_Color.x, m_Color.y, m_Color.z, m_Color.w,  // bottom left 2
				m_Color.x, m_Color.y, m_Color.z, m_Color.w,  // top left 3
			};
			uint32_t indices[6] = {
				0, 1, 3,
				1, 2, 3,
			};

			m_VertexArray = std::make_shared<VertexArray>();
			m_VertexArray->bind();

			m_VertexBuffer.bind();
			m_VertexArray->setVertexData(0, 3, 12, vertices);
			m_VertexBuffer.unbind();

			m_ColorBuffer.bind();
			m_VertexArray->setVertexData(1, 4, 16, colors);
			m_ColorBuffer.unbind();

			m_IndexBuffer = std::make_shared<IndexBuffer>(6);
			m_IndexBuffer->bind();
			m_VertexArray->setIndexData(6, indices);
			m_IndexBuffer->unbind();

			m_VertexArray->unbind();

		}

		Renderable2D::~Renderable2D() {

		}
	}
}