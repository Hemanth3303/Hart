#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		Renderable2D::Renderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, Shader& shader)
			:m_Position(position), m_Size(size), m_Color(color), m_Shader(shader) {

			m_VertexArray = new VertexArray();
			
			GLfloat vertices[] = {
				0, 0, 0,
				0, m_Size.y, 0,
				m_Size.x, m_Size.y, 0,
				m_Size.x, 0, 0
			};

			GLfloat colors[] = {
				m_Color.x, m_Color.y, m_Color.z, m_Color.w,
				m_Color.x, m_Color.y, m_Color.z, m_Color.w,
				m_Color.x, m_Color.y, m_Color.z, m_Color.w,
				m_Color.x, m_Color.y, m_Color.z, m_Color.w,
			};

			m_VertexArray->addBuffer(new Buffer(vertices, 12, 3), 0);//4*3 elements
			m_VertexArray->addBuffer(new Buffer(colors, 16, 4), 1);//4*4 elements

			GLuint indices[] = {
				0, 1, 2,
				2, 3, 0,
			};

			m_IndexBuffer = new IndexBuffer(indices, 6);

		}

		Renderable2D::~Renderable2D() {
			delete m_VertexArray;
			delete m_IndexBuffer;
		}
	}
}