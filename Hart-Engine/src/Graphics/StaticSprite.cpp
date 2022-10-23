#include "HartPch.hpp"
#include "StaticSprite.hpp"

namespace Hart {
	namespace Graphics {
		StaticSprite::StaticSprite(float x, float y, float width, float height, const Color& color, Shader& shader)
			: Renderable2D(Maths::Vec3(x, y, 0), Maths::Vec2(width, height), color), m_Shader(shader) {

			m_VertexArray = std::make_unique<VertexArray>();

			//vertices are aranged in this way to make their orgigin at the center rather than at a corner
			GLfloat vertices[] = {
				-m_Size.x / 2, -m_Size.y / 2, 0,  //from (-width, -height)
				-m_Size.x / 2,  m_Size.y / 2, 0,  //to (-width, height)
				 m_Size.x / 2,  m_Size.y / 2, 0,  //to (width, height)
				 m_Size.x / 2, -m_Size.y / 2, 0,  //to (width, -height)
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