#include "HartPch.hpp"
#include "StaticSprite.hpp"

namespace Hart {
	namespace Graphics {
		StaticSprite::StaticSprite(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, Shader& shader) 
			: Renderable2D(position, size, color), m_Shader(shader) {

			m_VertexArray = std::make_unique<VertexArray>();

			GLfloat vertices[] = {
				0, 0, 0,                    //from (0, 0, 0)
				0, m_Size.y, 0,             //to (0, y, 0)
				m_Size.x, m_Size.y, 0,      //to (x, y, 0)
				m_Size.x, 0, 0              //to (x, 0, 0)
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

			m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
		}

		StaticSprite::~StaticSprite() {

		}
	}
}