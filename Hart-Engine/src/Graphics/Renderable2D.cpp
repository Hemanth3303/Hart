#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		Renderable2D::Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, Shader* shader) 
			:m_Position(position), m_Size(size), m_Color(color), m_Shader(shader) {

			float vertices[12] = {
				 100.f,  100.f, 0.0f,  // top right
				 100.f, -100.f, 0.0f,  // bottom right
				-100.f, -100.f, 0.0f,  // bottom left
				-100.f,  100.f, 0.0f   // top left 
			};
			float colors[16] = {
				1.0f, 0.0f,  0.0f, 1.0f,  // top right
				0.0f, 1.0f,  0.0f, 1.0f,  // bottom right
				0.0f, 0.0f,  1.0f, 1.0f,  // bottom left
				0.5f, 0.25f, 0.5f, 1.0f,  // top left 
			};
			uint32_t indices[6] = {
				0, 1, 3,
				1, 2, 3,
			};

			m_VertexArray = new VertexArray();
			m_VertexArray->bind();

			m_VertexBuffer.bind();
			m_VertexArray->setVertexData(0, 3, 12, vertices);
			m_VertexBuffer.unbind();

			m_ColorBuffer.bind();
			m_VertexArray->setVertexData(1, 4, 16, colors);
			m_ColorBuffer.unbind();

			m_IndexBuffer = new IndexBuffer(6);
			m_IndexBuffer->bind();
			m_VertexArray->setIndexData(6, indices);
			m_IndexBuffer->unbind();

			m_VertexArray->unbind();

		}

		Renderable2D::~Renderable2D() {
			delete m_IndexBuffer;
			delete m_VertexArray;
		}
	}
}