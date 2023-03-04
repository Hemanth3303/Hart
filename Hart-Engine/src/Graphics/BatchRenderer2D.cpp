#include "HartPch.hpp"
#include "BatchRenderer2D.hpp"

namespace Hart {
	namespace Graphics {
        BatchRenderer2D::BatchRenderer2D() {
			init();
        }

        BatchRenderer2D::~BatchRenderer2D() {

        }

        void BatchRenderer2D::begin() {
			m_VertexBuffer.bind();
			m_Buffer = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        }

        void BatchRenderer2D::submit(const Renderable2D* renderable) {
			const Maths::Vec3& position = renderable->getPosition();
			const Maths::Vec2& size = renderable->getSize();
			const Maths::Vec4& color = renderable->getColor();

			m_Buffer->position = position;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->position = Maths::Vec3(position.x, position.y + size.y, position.z);
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->position = Maths::Vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->position = Maths::Vec3(position.x + size.x, position.y, position.z);
			m_Buffer->color = color;
			m_Buffer++;

			m_IndexCount += 6;
        }

        void BatchRenderer2D::flush() {
			m_VertexArray.bind();
			m_IndexBuffer->bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

			m_IndexBuffer->unbind();
			m_VertexArray.unbind();

			m_IndexCount = 0;
        }

        void BatchRenderer2D::end() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			m_VertexBuffer.unbind();
        }

        void BatchRenderer2D::init() {
			m_VertexArray.bind();
			m_VertexBuffer.bind();
			m_VertexArray.setVertexData(SHADER_VERTEX_INDEX, 3, RENDERER_BUFFER_SIZE, RENDERER_VERTEX_SIZE, 0, GL_DYNAMIC_DRAW, static_cast<const void*>(0));
			m_VertexArray.setVertexData(SHADER_COLOR_INDEX, 4, RENDERER_BUFFER_SIZE, RENDERER_VERTEX_SIZE, 0, GL_DYNAMIC_DRAW, reinterpret_cast<const void*>(offsetof(VertexData, VertexData::color)));
			m_VertexBuffer.unbind();

			std::vector<uint32_t> indices;
			indices.resize(RENDERER_INDICES_SIZE);
			int32_t offset = 0;
			for (uint32_t i = 0; i < RENDERER_INDICES_SIZE; i+=6) {
				indices[i] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}
			m_IndexBuffer = std::make_unique<IndexBuffer>(RENDERER_INDICES_SIZE);
			m_IndexBuffer->bind();
			m_VertexArray.setIndexData(RENDERER_INDICES_SIZE, indices.data(), GL_STATIC_DRAW);
			m_IndexBuffer->unbind();
			m_VertexArray.unbind();
        }

    }
}