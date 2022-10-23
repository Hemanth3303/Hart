#include "HartPch.hpp"
#include "BatchRenderer2D.hpp"

namespace Hart {
	namespace Graphics {
		BatchRenderer2D::BatchRenderer2D() {
			init();
			HART_ENGINE_INFO("BatchRenderer2D initialized");
		}

		BatchRenderer2D::~BatchRenderer2D() {
			glDeleteBuffers(1, &m_VBO);
			glDeleteVertexArrays(1, &m_VAO);
			delete[] m_Indices;
			HART_ENGINE_INFO("BatchRenderer2D deinitialized");
		}

		void BatchRenderer2D::begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable2d) {
			const Maths::Vec3& position = renderable2d->getPosition();
			const Maths::Vec2& size = renderable2d->getSize();
			const Maths::Vec4& color = renderable2d->getColor();

			//centered around origin
			m_Buffer->vertex = Maths::Vec3((position.x - size.x) / 2, (position.y - size.y) / 2, position.z);
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = Maths::Vec3((position.x - size.x) / 2, (position.y + size.y) / 2, position.z);
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = Maths::Vec3((position.x + size.x) / 2, (position.y + size.y) / 2, position.z);
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = Maths::Vec3((position.x + size.x) / 2, (position.y - size.y) / 2, position.z);
			m_Buffer->color = color;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void BatchRenderer2D::end() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush() {
			glBindVertexArray(m_VAO);
			m_IndexBuffer->bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);

			m_IndexBuffer->unbind();
			glBindVertexArray(0);

			m_IndexCount = 0;
		}

		void BatchRenderer2D::init() {
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::vertex)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			m_Indices=new GLuint[RENDERER_INDICES_SIZE];

			int32_t offset = 0;

			for (int32_t i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
				m_Indices[i + 0] = offset + 0;
				m_Indices[i + 1] = offset + 1;
				m_Indices[i + 2] = offset + 2;

				m_Indices[i + 3] = offset + 2;
				m_Indices[i + 4] = offset + 3;
				m_Indices[i + 5] = offset + 0;

				offset += 4;
			}
			m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices, RENDERER_INDICES_SIZE);
			glBindVertexArray(0);
		}
	}
}